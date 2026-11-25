(in-package :pvs)

;;; Nested array lambdas receive a C type name from the enclosing array emitter.
;;; Resolve that name back to its existing IR type before translating the lambda.
;;; Otherwise the generator calls IR-RANGE on a string (e.g. Rijndael_array_0).
;;; This changes only the generator's type lookup, not the PVS specification.
(defmethod ir2c* :around ((expr ir-lambda) return-var return-type)
  (if (stringp return-type)
      (let ((info (find return-type *c-type-info-table* :key #'tname :test #'string=)))
        (unless info (error "Unknown generated lambda type: ~a" return-type))
        (call-next-method expr return-var (type-info-texpr info)))
      (call-next-method)))

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
