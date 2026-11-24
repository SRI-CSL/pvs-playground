(in-package :pvs)
(setq *noninteractive* t *proof-prompt-behavior* :noquestions *proceed-without-asking* t)

(defun inverse-replay (name)
  (tc name)
  (let ((th (get-typechecked-theory name)) (count 0) (*noninteractive-timeout* 240))
    (unless th (error "Could not typecheck ~a" name))
    (read-strategies-files)
    ;; provable-formulas includes generated TCCs in the ASSUMING section.
    ;; The _TEST_ declarations have separate generated-C drivers.
    (dolist (d (provable-formulas th))
      (unless (or (test-formula? d) (and (generated-by d) (not (tcc? d))))
        (unless (and (justification d)
                     (let ((result (prove-decl d :strategy '(then (rerun) (quit)))))
                       (and result (eq (status-flag result) '!))))
          (error "Replay failed for ~a.~a" name (id d)))
        (incf count)))
    (format t "~%Checked ~d saved declarations in ~a.~%" count name)))
