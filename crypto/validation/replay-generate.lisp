(in-package :pvs)
(setq *noninteractive* t *proceed-without-asking* t *proof-prompt-behavior* :noquestions)

;;; Run inside a fresh disposable context with only source and saved proofs.
(defun crypto-replay (name)
  (let ((th (get-typechecked-theory name nil t)))
    (unless th (error "Theory not found: ~a" name))
    (read-strategies-files)
    (let ((checked 0))
      (dolist (d (theory th))
        ;; Datatype declarations synthesize constructor axioms. TCCs
        ;; and explicit local theorems carry replayable proof obligations.
        (when (and (formula-decl? d) (not (test-formula? d))
                   (or (tcc? d) (not (generated-by d))))
          (unless (and (justification d)
                       (eq '! (status-flag (prove-decl d :strategy '(then (rerun) (quit))))))
            (error "Replay failed: ~a.~a" name (id d)))
          (incf checked)))
      (format t "~%Checked ~d saved declarations in ~a.~%" checked name))
    th))

(defun crypto-replay-generate (name &optional (replay t))
  (let ((th (if replay (crypto-replay name) (get-typechecked-theory name nil t)))
        (*all-mono-theories* nil))
    ;; Use the installed precompiled Prelude. Rebuild each application module
    ;; separately, in import order, without regenerating the global Prelude.
    (dolist (dep (all-imported-theories th))
      (unless (from-prelude? dep) (pvs2c-theory* dep t)))
    (pvs2c-theory* th t)
    (format t "~%CRYPTO-OK ~a~%" name)))
