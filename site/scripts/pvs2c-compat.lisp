(in-package :pvs)

;;; C structs must retain their field names. Logical alpha-equivalence alone
;;; can otherwise merge an affine point (finite,x,y) with a signature (ok,r,s).
;;; Restrict this correction to the C type cache, leaving PVS/IR equality alone.
(defvar *browser-c-type-lookup* nil)
(defvar *browser-original-c-type-info* (symbol-function 'get-c-type-info))
(defun get-c-type-info (type)
  (let ((*browser-c-type-lookup* t))
    (funcall *browser-original-c-type-info* type)))
(defmethod ir2c-tequal* :around ((a ir-fieldtype) (b ir-fieldtype) bindings)
  (and (or (not *browser-c-type-lookup*) (eq (ir-id a) (ir-id b)))
       (call-next-method)))

;;; Enumerations already have an IR subrange representation. Emit that scalar
;;; type rather than an undeclared ADT pointer name.
(defmethod add-c-type-definition :around ((type ir-typename) &optional name)
  (if (ir-subrange? (ir-type-defn type))
      (add-c-type-definition (ir-type-defn type))
      (call-next-method)))

;;; A closure invocation consumes a reference. Materializing its elements into
;;; an array must retain the closure for each call; the owning record releases
;;; its original reference after the conversion.
(defmethod copy-type* :around ((left ir-arraytype) (right ir-funtype) lhs rhs)
  (let ((instructions (call-next-method)))
    (dolist (instruction instructions)
      (when (typep instruction 'for-instr)
        (push (format nil "~a->count++" rhs) (for-body instruction))))
    instructions))

;;; The lambda emitter adds one to a literal upper index. For a fixed array,
;;; SIZE can instead be its cardinality; use the actual domain upper bound.
(defvar *browser-original-array-size* (symbol-function 'array-size-expr))
(defun array-size-expr (type)
  (let ((domain (ir-domain type)))
    (if (and (ir-subrange? domain) (integerp (ir-high domain)) (null (ir-high-expr domain)))
        (ir-high domain)
        (funcall *browser-original-array-size* type))))

;;; Function tables return GMP pointers. Their equality helper must use the
;;; same pointer type, rather than trying to initialize GMP's array typedef.
(defun browser-replace-text (text before after)
  (with-output-to-string (out)
    (loop with start = 0 for pos = (search before text :start2 start)
          do (write-string text out :start start :end pos)
          while pos do (write-string after out) (setf start (+ pos (length before))))))
(defvar *browser-original-function-equal* (symbol-function 'make-function-equal-info))
(defun make-function-equal-info (root type declarations arguments)
  (let ((info (funcall *browser-original-function-equal* root type declarations arguments)))
    (dolist (kind '("mpz" "mpq"))
      (dolist (variable '("xval" "yval"))
        (setf (op-defn info) (browser-replace-text (op-defn info)
          (format nil "~a_t ~a =" kind variable) (format nil "~a_ptr_t ~a =" kind variable)))))
    ;; A declaration-local bound is unavailable in this type-level helper.
    ;; Algorithms still use their closures normally. Comparing such functions
    ;; is unsupported: fail the run explicitly, never manufacture an equality.
    (let* ((definition (if (ir-typename? type) (ir-type-defn type) type))
           (domain (and (ir-funtype? definition) (ir-domain definition))))
      (when (and (ir-subrange? domain)
                 (some (lambda (bound)
                         (and bound (some (lambda (var) (not (ir-const-formal? var)))
                                          (wrap-pvs2ir-freevars bound nil))))
                       (list (ir-low-expr domain) (ir-high-expr domain))))
        (setf (op-defn info) (format nil
          "bool_t equal_~a(~a_t x, ~a_t y~a){ pvs2cerror(\"Unsupported PVS2C function equality with a dynamic bound\", 2); return false; }"
          root root root declarations))))
    info))

;;; Array element bodies receive a C type name from the enclosing emitter.
;;; Resolve it back to its IR type for both nested arrays and reference counts.
;;; Treating a record's C name as a scalar loses the element's ownership and
;;; frees borrowed constants or local results while the array still uses them.
;;; This changes only the generator's type lookup, not the PVS specification.
(defun browser-ir-return-type (type)
  (if (or (stringp type) (symbolp type))
      (let ((info (find (string type) *c-type-info-table*
                        :key (lambda (entry) (string (tname entry))) :test #'string=)))
        (or (and info (type-info-texpr info)) type))
      type))
(defmethod ir2c* :around ((expr ir-expr) return-var return-type)
  (call-next-method expr return-var (browser-ir-return-type return-type)))

;;; The stock application emitter creates copies of non-last GMP arguments,
;;; but invokes the function with the originals. Pass the intended copies so
;;; comparisons and consuming calls cannot clear a value that is still live.
(defmethod ir2c* :around ((expr ir-apply) return-var return-type)
  (let* ((function (ir-func expr)) (variable (get-ir-last-var function)))
    (if (and (ir-variable? variable) (ir-array? (ir-vtype variable)))
        (call-next-method)
        (let* ((arguments (ir-args expr)) (parameters (ir-params expr))
               (copies (loop for arg in arguments
                             when (and (not (ir-last? arg)) (mpnumber-type? (ir2c-type (ir-vtype arg))))
                             collect (cons arg (mk-ir-variable (new-irvar) (ir-vtype arg)))))
               (owned (mapcar (lambda (arg) (or (cdr (assq arg copies)) arg)) arguments))
               (copy-code (loop for (original . copy) in copies
                                for type = (ir2c-type (ir-vtype original))
                                collect (format nil "~a_ptr_t ~a; ~a_mk_set(~a, ~a)"
                                          type (ir-name copy) type (ir-name copy) (ir-name original))))
               (retain-code (loop for arg in (append owned parameters)
                                  when (and (not (ir-last? arg)) (ir-reference-type? (ir-vtype (get-ir-last-var arg))))
                                  collect (format nil "~a->count++" (ir-name arg)))))
          (append copy-code retain-code
                  (ir2c-function-apply return-var (browser-ir-return-type return-type) function owned parameters))))))

;;; Scalar-element array update definitions omit theory parameters that their
;;; generated declarations already include. Keep their signatures identical.
(defvar *browser-original-array-update-defn* (symbol-function 'make-array-update-defn))
(defun make-array-update-defn (name root range c-range arguments parameters)
  (let ((definition (funcall *browser-original-array-update-defn*
                             name root range c-range arguments parameters)))
    (if (and (not (ir-reference-type? range)) (plusp (length parameters)))
        (let ((end (search "){" definition)))
          (unless end (error "Unexpected array update definition: ~a" name))
          (concatenate 'string (subseq definition 0 end) parameters (subseq definition end)))
        definition)))
