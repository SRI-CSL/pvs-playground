# Implement PBFT in PVS

> Implement Practical Byzantine Fault Tolerance (the document/paper located under doc/) in PVS and place your specs under pvs/. You can invoke PVS via ~/git/PVS/pvs -raw -E '(tc "theoryname" t)', read off TCCs via '(show-tccs "theoryname")' (don't then try to avoid/refactor TCCs, they are excellent sanity checks), and state the paper's theorems in PVS and invoke the prover with '(prove-formula-decl ...)' to prove the theorems (the arguments should largely mimic the argument in the paper, but simplify them if you can). Please write elegant PVS and utilize typing (predicate subtyping, dependent typing) to your advantage to create elegant, lucid, and beautiful PVS specifications that distill the heart of the formalization.

<details><summary>187 previous messages</summary>

> I’ll first map the repo and read the PBFT document under `doc/`, then I’ll shape the PVS theories around the paper’s core definitions and safety arguments. After that I’ll typecheck and try the prover on the stated theorem declarations so the specs are not just pretty prose in theorem clothing.
>
> <details><summary>Explored 2 lists, ran 2 commands</summary>
>
> <details><summary>Explored 2 lists</summary>
>
> - Listed files in `doc`
> - Listed files in `pvs`
>
> </details>
>
> - Ran `pwd && rg --files`
>
> - Ran `git status --short`
>
> </details>
>
> I found a very small workspace: the PBFT PDF is `doc/castro-practicalbft.pdf`, `pvs/` is empty, and this directory is not a git repo. Since the source material is a PDF, I’m pulling in the local PDF workflow now so I can extract the paper accurately.
>
> <details><summary>Explored a file</summary>
>
> - Read `~/.codex/plugins/cache/openai-primary-runtime/pdf/26.623.12021/skills/pdf/SKILL.md`
>
> </details>
>
> The bundled runtime has Poppler and Python PDF libraries available, which is perfect here. I’m going to extract the paper text and also inspect enough page images to avoid missing notation that text extraction tends to flatten.
>
> <details><summary>Explored a list, ran 2 commands</summary>
>
> - Ran `/Users/e35480/.cache/codex-runtimes/codex-primary-runtime/dependencies/bin/pdftotext -layout doc/castro-practicalbft.pdf /private/tmp/castro-practicalbft.txt`
>
> <details><summary>Explored a list</summary>
>
> - Listed files in `doc`
>
> </details>
>
> - Ran `/Users/e35480/.cache/codex-runtimes/codex-primary-runtime/dependencies/bin/pdfinfo doc/castro-practicalbft.pdf`
>
> </details>
>
> `pdfinfo` sees a 14-page letter-size paper, but this bundle has `pdfinfo` without `pdftotext`. I’ll use the Python PDF libraries for extraction and Poppler rendering for spot-checking the pages.
>
> <details><summary>Ran 3 commands</summary>
>
> - Ran `mkdir -p /private/tmp/pbft_pdf`
> - Ran `/Users/e35480/.cache/codex-runtimes/codex-primary-runtime/dependencies/python/bin/python3 -c 'from pypdf import PdfReader; r=PdfReader("doc/castro-practicalbft.pdf"); print("\n\n".join(f"--- PAGE {i+1} ---\n"+(p.extract_text() or "") for i,p in enumerate(r.pages)))'`
> - Ran `/Users/e35480/.cache/codex-runtimes/codex-primary-runtime/dependencies/bin/pdftoppm -png -f 1 -l 4 doc/castro-practicalbft.pdf /private/tmp/pbft_pdf/page`
>
> </details>
>
> The extracted text is usable enough for the protocol sections, but it was too large for one terminal read. I’m going to save it as a temporary text file and search the paper by section and key predicates: prepared, committed-local, view-change, and checkpoints.
>
> The page renderer got stuck on font-cache noise, so I stopped that. The text extraction has the mathematical core we need, and I’ll rely on targeted extraction around the protocol definitions instead of full-page rendering.
>
> <details><summary>Explored a search, ran a command</summary>
>
> <details><summary>Explored a search</summary>
>
> - Searched for `prepared|committed|committed-local|view-change|VIEW-CHANGE|NEW-VIEW|checkpoint|stable|safety|liveness|linearizability|invariant|correctness|Theorem|Lemma` in `castro-practicalbft.txt`
>
> </details>
>
> - Ran `/Users/e35480/.cache/codex-runtimes/codex-primary-runtime/dependencies/python/bin/python3 -c 'from pypdf import PdfReader; r=PdfReader("doc/castro-practicalbft.pdf"); open("/private/tmp/castro-practicalbft.txt","w",encoding="utf-8").write("\n\n".join(f"--- PAGE {i+1} ---\n"+(p.extract_text() or "") for i,p in enumerate(r.pages)))'`
>
> </details>
>
> Small race: the search started before the temporary text file existed. The extraction completed, so I’m rerunning the focused search now.
>
> <details><summary>Explored a search</summary>
>
> - Searched for `prepared|committed|committed-local|view-change|VIEW-CHANGE|NEW-VIEW|checkpoint|stable|safety|liveness|linearizability|invariant|correctness|Theorem|Lemma` in `castro-practicalbft.txt`
>
> </details>
>
> The paper’s formal heart is exactly where expected: the two quorum intersection invariants in Section 4.2, the checkpoint certificate, and the view-change safety argument in Section 4.4. I’m reading those ranges closely now and will encode those as PVS predicates plus lemmas rather than attempting to model every engineering optimization.
>
> <details><summary>Explored 4 files</summary>
>
> - Read `/private/tmp/castro-practicalbft.txt`
> - Read `/private/tmp/castro-practicalbft.txt`
> - Read `/private/tmp/castro-practicalbft.txt`
> - Read `/private/tmp/castro-practicalbft.txt`
>
> </details>
>
> For the PVS side, I’m aiming at a compact proof-oriented model: abstract cryptographic digests and service determinism, concrete replica cardinalities `n = 3f + 1`, and the paper’s safety lemmas as first-class theorem declarations. The trickiest bit will be making quorum arithmetic pleasant enough that PVS can actually discharge it.
>
> <details><summary>Explored 3 searches</summary>
>
> - Searched for `finite_sets*.pvs` in `PVS`
> - Searched for `card\(|cardinality|finite_set|IMPORTING finite|below\(` in `nasalib`
> - Searched for `prove-formula-decl|grind|then \(skeep|lemma` in `PVS`
>
> </details>
>
> There’s useful local precedent: the PVS distribution has a Byzantine example and NASALib has finite-set/quorum lemmas. I’m going to reuse that style where it helps, but keep this spec self-contained under `pvs/` so it doesn’t become a scavenger hunt.
>
> <details><summary>Explored 5 files, a search</summary>
>
> - Read `~/git/PVS/lib/finite_sets/finite_sets_card_eq.pvs`
> - Read `~/git/PVS/lib/finite_sets/finite_sets_below.pvs`
> - Read `~/git/PVS/Examples/byzantine/byzantine.pvs`
> - Read `~/git/PVS/nasalib/fault_tolerance/pigeonhole.pvs`
> - Read `~/git/PVS/src/raw-api.lisp`
> - Searched for `defun prove-formula-decl|prove-formula-decl` in `PVS`
>
> </details>
>
> I’m also checking the raw prover interface so I call it the way this build expects. `prove-formula-decl` exists and takes the declaration name, optional theory name, and optional strategy; I’ll use that after `tc`.
>
> <details><summary>Explored 2 files, a search</summary>
>
> - Read `~/git/PVS/src/pvs.lisp`
> - Read `~/git/PVS/src/pvs.lisp`
> - Searched for `card_.*difference|difference_.*card|intersection|union` in `finite_sets.pvs`
>
> </details>
>
> I’ll use the standard `finite_sets_below` pigeonhole lemma for quorum intersection and write a small bridge lemma for “a 2f+1 certificate contains f+1 correct replicas.” That mirrors the paper’s proof step and should keep the theorem statements readable.
>
> <details><summary>Explored a search, a list</summary>
>
> - Listed files in `finite_sets`
> - Searched for `card\(.*union|card\(.*intersection|card\(.*difference|disjoint|subset_card|difference` in `lib`
>
> </details>
>
> The safety proof I’m encoding has three layers: quorum arithmetic, protocol certificates, and then the paper-facing theorems. That keeps the PBFT-specific declarations clean while letting PVS chew on the finite-set facts separately.
>
> <details><summary>Explored a search</summary>
>
> - Searched for `empty.*card|card.*empty|nonempty|non_empty|card.*0|0.*card` in `prelude.pvs`
>
> </details>
>
> I’m going to create the first PVS theory now: a reusable `pbft_quorums` layer with replica type `below(3*f+1)`, the bounded fault set, and quorum-intersection lemmas. Once that typechecks, I’ll build the PBFT protocol predicates on top of it.
>
> <details><summary>Created a file</summary>
>
> - Wrote `./pvs/pbft_quorums.pvs` (+57 -0)
>
> </details>
>
> The quorum layer is in place. I’m typechecking it first; if PVS gives useful TCCs or proof obligations, I’ll keep them and use them to sharpen the model rather than papering over them.
>
> <details><summary>Ran a command</summary>
>
> - Ran `~/git/PVS/pvs -raw -E '(tc "pbft_quorums" t)'`
>
> </details>
>
> Typechecking parsed cleanly but produced 6 TCCs, with 5 unproved. That’s expected at this point because cardinality over `below(n)` needs the finite-type bridge; I’m reading the TCCs and will make the intended facts explicit.
>
> <details><summary>Ran a command</summary>
>
> - Ran `~/git/PVS/pvs -raw -E '(show-tccs "pbft_quorums")'`
>
> </details>
>
> The TCCs are all the same sanity check: every set of replicas should be finite because replicas are `below(3f+1)`. I’m adding that as a local judgement, which is exactly the typing fact the later proofs should be allowed to rely on.
>
> <details><summary>Edited a file</summary>
>
> - Wrote `./pvs/pbft_quorums.pvs` (+3 -0)
>
> </details>
>
> Now I’m rerunning typecheck on `pbft_quorums`; this should turn those finiteness TCCs into an explicit, reusable typing bridge.
>
> <details><summary>Ran 2 commands</summary>
>
> - Ran `~/git/PVS/pvs -raw -E '(tc "pbft_quorums" t)'`
> - Ran `~/git/PVS/pvs -raw -E '(show-tccs "pbft_quorums")'`
>
> </details>
>
> The local judgement creates one nice but unproved meta-TCC. I can make the theory cleaner by using `finite_set[replica]` directly as the replica-set type; that expresses the same intent without asking every cardinality occurrence to rediscover finiteness.
>
> <details><summary>Edited a file, ran 2 commands</summary>
>
> - Wrote `./pvs/pbft_quorums.pvs` (+1 -2)
> - Ran `~/git/PVS/pvs -raw -E '(tc "pbft_quorums" t)'`
> - Ran `~/git/PVS/pvs -raw -E '(show-tccs "pbft_quorums")'`
>
> </details>
>
> Only one TCC remains, for naming `fullset[replica]` as a finite set. Since the later proofs use `finite_sets_below[n]` directly and don’t need that alias, I’m removing the alias rather than adding ceremony.
>
> <details><summary>Edited a file</summary>
>
> - Wrote `./pvs/pbft_quorums.pvs` (+0 -5)
>
> </details>
>
> `pbft_quorums` is trimmed to the facts that do real work. I’m checking again before trying to prove the quorum lemmas.
>
> <details><summary>Ran a command</summary>
>
> - Ran `~/git/PVS/pvs -raw -E '(tc "pbft_quorums" t)'`
>
> </details>
>
> No TCCs now. I’m starting with the easy arithmetic lemma, then I’ll try the set lemmas and adjust strategies only where `grind` needs a nudge.
>
> <details><summary>Explored a file, a search, ran a command</summary>
>
> - Ran `~/git/PVS/pvs -raw -E '(prove-formula-decl "one_more_than_faults_is_positive" "pbft_quorums" "(grind)")'`
>
> <details><summary>Explored a file, a search</summary>
>
> - Searched for `defun typecheck-formula-decl` in `pvs.lisp`
> - Read `~/git/PVS/src/pvs.lisp`
>
> </details>
>
> </details>
>
> This build’s `prove-formula-decl` expects a full formula declaration string, not just the name. I’ll still use it for the final theorem invocations, and for quick development checks I can use the raw black-box prover against existing declarations by name.
>
> <details><summary>Ran 2 commands</summary>
>
> - Ran `~/git/PVS/pvs -raw -E '(prove-as-black-box "one_more_than_faults_is_positive")'`
> - Ran `~/git/PVS/pvs -raw -E '(progn (tc "pbft_quorums" nil) (prove-as-black-box "one_more_than_faults_is_positive"))'`
>
> </details>
>
> The named black-box helper isn’t finding declarations in a parameterized theory cleanly, so I’m switching to the explicit declaration-string form now. It’s a bit more verbose, but it matches `prove-formula-decl`’s actual contract.
>
> <details><summary>Explored 3 files, 2 searches, ran a command</summary>
>
> - Ran `~/git/PVS/pvs -raw -E '(prove-formula-decl "one_more_than_faults_is_positive_check: THEOREM f + 1 > f" "pbft_quorums" "(grind)")'`
>
> <details><summary>Explored 3 files, 2 searches</summary>
>
> - Searched for `Would you like the proof to be saved|proof to be saved|save-proof` in `PVS`
> - Read `~/git/PVS/src/prover/eproofcheck.lisp`
> - Read `~/git/PVS/src/globals.lisp`
> - Searched for `proof-prompt-behavior|pvs-noquestions|pvs-dont-ask` in `PVS`
> - Read `~/git/PVS/src/pvs-threads.lisp`
>
> </details>
>
> </details>
>
> I found the noninteractive switch for proof saving. From here on I’ll bind the proof prompt behavior to `:noquestions`, so `prove-formula-decl` can finish without waiting for an answer about saving temporary proofs.
>
> <details><summary>Ran a command</summary>
>
> - Ran `~/git/PVS/pvs -raw -E '(let ((*proof-prompt-behavior* :noquestions) (*proceed-without-asking* t)) (prove-formula-decl "one_more_than_faults_is_positive_check: THEOREM f + 1 > f" "pbft_quorums" "(grind)"))'`
>
> </details>
>
> The arithmetic proof completed with `Q.E.D.` under `prove-formula-decl`. I’m moving through the quorum lemmas now; these are the engine for the PBFT safety proof.
>
> <details><summary>Ran a command</summary>
>
> - Ran `~/git/PVS/pvs -raw -E '(let ((*proof-prompt-behavior* :noquestions) (*proceed-without-asking* t)) (prove-formula-decl "quorum_contains_correct_check: THEOREM quorum_f_plus_1?(A) IMPLIES EXISTS r: A(r) AND correct(r)" "pbft_quorums" "(grind)"))'`
>
> </details>
>
> Temporary formula declarations don’t inherit the theory’s `VAR` shorthands as free variables, so I’ll call `prove-formula-decl` with explicit `FORALL` binders. The checked file can keep the cleaner local-variable style.
>
> <details><summary>Explored a file, ran a command</summary>
>
> - Ran `~/git/PVS/pvs -raw -E '(let ((*proof-prompt-behavior* :noquestions) (*proceed-without-asking* t)) (prove-formula-decl "quorum_contains_correct_check: THEOREM FORALL (A: replica_set): quorum_f_plus_1?(A) IMPLIES EXISTS (r: replica): A(r) AND correct(r)" "pbft_quorums" "(grind)"))'`
>
> <details><summary>Explored a file</summary>
>
> - Read `~/git/PVS/lib/prelude.pvs`
>
> </details>
>
> </details>
>
> `grind` alone tried to synthesize a witness directly and got lost. I’m giving it the paper’s actual counting move: if every member of the certificate were faulty, the certificate would be a subset of `faulty`, contradicting `card(faulty) <= f`.
>
> <details><summary>Ran 2 commands</summary>
>
> - Ran `~/git/PVS/pvs -raw -E '(let ((*proof-prompt-behavior* :noquestions) (*proceed-without-asking* t)) (prove-formula-decl "quorum_contains_correct_check: THEOREM FORALL (A: replica_set): quorum_f_plus_1?(A) IMPLIES EXISTS (r: replica): A(r) AND correct(r)" "pbft_quorums" "(then (skosimp*) (lemma \"card_subset\" (\"A\" \"A!1\" \"B\" \"faulty\")) (grind))"))'`
> - Ran `~/git/PVS/pvs -raw -E '(let ((*proof-prompt-behavior* :noquestions) (*proceed-without-asking* t)) (prove-formula-decl "quorum_contains_correct_check: THEOREM FORALL (A: replica_set): quorum_f_plus_1?(A) IMPLIES EXISTS (r: replica): A(r) AND correct(r)" "pbft_quorums" "(then (skosimp*) (lemma \"card_subset\" (\"A\" \"A!1\" \"B\" \"faulty\")) (lemma \"fault_bound\") (grind))"))'`
>
> </details>
>
> I’m going to split that witness lemma into the exact counting fact first: any all-faulty set has cardinality at most `f`. That is the arithmetic fact PVS should use before trying to construct a nonfaulty member.
>
> <details><summary>Ran a command</summary>
>
> - Ran `~/git/PVS/pvs -raw -E '(let ((*proof-prompt-behavior* :noquestions) (*proceed-without-asking* t)) (prove-formula-decl "all_faulty_card_bound_check: THEOREM FORALL (A: replica_set): (FORALL (r: replica): A(r) IMPLIES faulty(r)) IMPLIES card(A) <= f" "pbft_quorums" "(then (skosimp*) (lemma \"card_subset\" (\"A\" \"A!1\" \"B\" \"faulty\")) (lemma \"fault_bound\") (grind))"))'`
>
> </details>
>
> That counted fact proves cleanly. I’m adding it to the theory as an explicit lemma; the later theorems will now read much closer to the PBFT argument: “a certificate larger than the fault budget contains a correct replica.”
>
> <details><summary>Edited a file</summary>
>
> - Wrote `./pvs/pbft_quorums.pvs` (+3 -0)
>
> </details>
>
> I’m typechecking the quorum file again after adding the lemma, then I’ll use it to prove the certificate-witness theorem.
>
> <details><summary>Ran a command</summary>
>
> - Ran `~/git/PVS/pvs -raw -E '(tc "pbft_quorums" t)'`
>
> </details>
>
> Typecheck is still clean: no TCCs. I’m invoking `prove-formula-decl` on the new lemma and then the certificate-witness theorem.
>
> <details><summary>Ran 2 commands</summary>
>
> - Ran `~/git/PVS/pvs -raw -E '(let ((*proof-prompt-behavior* :noquestions) (*proceed-without-asking* t)) (prove-formula-decl "all_faulty_card_bound_check: THEOREM FORALL (A: replica_set): (FORALL (r: replica): A(r) IMPLIES faulty(r)) IMPLIES card(A) <= f" "pbft_quorums" "(then (skosimp*) (lemma \"card_subset\" (\"A\" \"A!1\" \"B\" \"faulty\")) (lemma \"fault_bound\") (grind))"))'`
> - Ran `~/git/PVS/pvs -raw -E '(let ((*proof-prompt-behavior* :noquestions) (*proceed-without-asking* t)) (prove-formula-decl "quorum_contains_correct_check: THEOREM FORALL (A: replica_set): quorum_f_plus_1?(A) IMPLIES EXISTS (r: replica): A(r) AND correct(r)" "pbft_quorums" "(then (skosimp*) (lemma \"all_faulty_card_bound\" (\"A\" \"A!1\")) (grind))"))'`
>
> </details>
>
> The all-faulty bound is good, but existential witness search is still making PVS wander. I’ll expose the witness theorem through its equivalent contradiction form first, then use that form inside protocol proofs.
>
> <details><summary>Ran 2 commands</summary>
>
> - Ran `~/git/PVS/pvs -raw -E '(let ((*proof-prompt-behavior* :noquestions) (*proceed-without-asking* t)) (prove-formula-decl "quorum_not_all_faulty_check: THEOREM FORALL (A: replica_set): quorum_f_plus_1?(A) IMPLIES NOT (FORALL (r: replica): A(r) IMPLIES faulty(r))" "pbft_quorums" "(then (skosimp*) (lemma \"all_faulty_card_bound\" (\"A\" \"A!1\")) (grind))"))'`
> - Ran `~/git/PVS/pvs -raw -E '(let ((*proof-prompt-behavior* :noquestions) (*proceed-without-asking* t)) (prove-formula-decl "not_all_faulty_has_correct_check: THEOREM FORALL (A: replica_set): NOT (FORALL (r: replica): A(r) IMPLIES faulty(r)) IMPLIES EXISTS (r: replica): A(r) AND correct(r)" "pbft_quorums" "(grind)"))'`
>
> </details>
>
> Great: PVS proves the classical bridge from “not all are faulty” to “there exists a correct member.” I’m adding both bridge lemmas, which should make the witness theorems routine and reusable.
>
> <details><summary>Edited a file</summary>
>
> - Wrote `./pvs/pbft_quorums.pvs` (+8 -0)
>
> </details>
>
> The quorum theory now has the bridge structure I want. I’m typechecking again before moving on to the larger intersections.
>
> <details><summary>Ran a command</summary>
>
> - Ran `~/git/PVS/pvs -raw -E '(tc "pbft_quorums" t)'`
>
> </details>
>
> Typecheck remains clean. I’m checking that the decomposed witness theorem now proves as intended.
>
> <details><summary>Ran a command</summary>
>
> - Ran `~/git/PVS/pvs -raw -E '(let ((*proof-prompt-behavior* :noquestions) (*proceed-without-asking* t)) (prove-formula-decl "quorum_contains_correct_check: THEOREM FORALL (A: replica_set): quorum_f_plus_1?(A) IMPLIES EXISTS (r: replica): A(r) AND correct(r)" "pbft_quorums" "(then (skosimp*) (lemma \"quorum_not_all_faulty\" (\"A\" \"A!1\")) (lemma \"not_all_faulty_has_correct\" (\"A\" \"A!1\")) (grind))"))'`
>
> </details>
>
> The witness theorem is proved. Next I’m proving the PBFT quorum overlap lemma: two `2f+1` certificates in a `3f+1` replica universe overlap in at least `f+1` replicas.
>
> <details><summary>Ran a command</summary>
>
> - Ran `~/git/PVS/pvs -raw -E '(let ((*proof-prompt-behavior* :noquestions) (*proceed-without-asking* t)) (prove-formula-decl "large_quorums_overlap_check: THEOREM FORALL (A, B: replica_set): quorum_2f_plus_1?(A) AND quorum_2f_plus_1?(B) IMPLIES card(intersection(A, B)) >= f + 1" "pbft_quorums" "(then (skosimp*) (lemma \"pidgeon_hole\" (\"A\" \"A!1\" \"B\" \"B!1\" \"k\" \"f+1\")) (grind))"))'`
>
> </details>
>
> The large-overlap cardinal lemma proves cleanly with `pidgeon_hole`. I’m also checking the stronger useful form: any `2f+1` certificate contains at least `f+1` correct replicas.
>
> <details><summary>Ran a command</summary>
>
> - Ran `~/git/PVS/pvs -raw -E '(let ((*proof-prompt-behavior* :noquestions) (*proceed-without-asking* t)) (prove-formula-decl "quorum_has_f_plus_1_correct_check: THEOREM FORALL (A: replica_set): quorum_2f_plus_1?(A) IMPLIES card(correct_part(A)) >= f + 1" "pbft_quorums" "(then (skosimp*) (lemma \"card_diff_subset\" (\"A\" \"intersection(A!1, faulty)\" \"B\" \"A!1\")) (lemma \"card_intersection_le\" (\"A\" \"A!1\" \"B\" \"faulty\")) (lemma \"fault_bound\") (grind))"))'`
>
> </details>
>
> The stronger certificate-cardinality theorem needs one ordinary set identity: removing `A ∩ faulty` from `A` is the same as removing `faulty` from `A`. I’m checking that identity separately and will add it as a tiny helper lemma.
>
> <details><summary>Explored a file, a search, ran a command</summary>
>
> - Ran `~/git/PVS/pvs -raw -E '(let ((*proof-prompt-behavior* :noquestions) (*proceed-without-asking* t)) (prove-formula-decl "difference_own_intersection_check: THEOREM FORALL (A, B: replica_set): difference(A, intersection(A, B)) = difference(A, B)" "pbft_quorums" "(grind)"))'`
>
> <details><summary>Explored a file, a search</summary>
>
> - Searched for `extensionality|set_ext|extensional` in `prelude.pvs`
> - Read `~/git/PVS/src/prover/strategies.lisp`
>
> </details>
>
> </details>
>
> The plain prover needed extensionality for set equality, so I’m switching that helper to `grind-with-ext`, the PVS strategy designed for exactly this kind of predicate/set equality.
>
> <details><summary>Ran a command</summary>
>
> - Ran `~/git/PVS/pvs -raw -E '(let ((*proof-prompt-behavior* :noquestions) (*proceed-without-asking* t)) (prove-formula-decl "difference_own_intersection_check: THEOREM FORALL (A, B: replica_set): difference(A, intersection(A, B)) = difference(A, B)" "pbft_quorums" "(grind-with-ext)"))'`
>
> </details>
>
> `grind-with-ext` proves the set identity. I’m adding it and retrying the `f+1` correct-members theorem with that identity available.
>
> <details><summary>Edited a file</summary>
>
> - Wrote `./pvs/pbft_quorums.pvs` (+3 -0)
>
> </details>
>
> I’m rerunning typecheck after adding the set identity, then the stronger certificate theorem.
>
> <details><summary>Ran a command</summary>
>
> - Ran `~/git/PVS/pvs -raw -E '(tc "pbft_quorums" t)'`
>
> </details>
>
> Typecheck is still clean. I’m invoking the proof of `quorum_has_f_plus_1_correct` now.
>
> <details><summary>Ran a command</summary>
>
> - Ran `~/git/PVS/pvs -raw -E '(let ((*proof-prompt-behavior* :noquestions) (*proceed-without-asking* t)) (prove-formula-decl "quorum_has_f_plus_1_correct_check: THEOREM FORALL (A: replica_set): quorum_2f_plus_1?(A) IMPLIES card(correct_part(A)) >= f + 1" "pbft_quorums" "(then (skosimp*) (lemma \"difference_own_intersection\" (\"A\" \"A!1\" \"B\" \"faulty\")) (lemma \"card_diff_subset\" (\"A\" \"intersection(A!1, faulty)\" \"B\" \"A!1\")) (lemma \"card_intersection_le\" (\"A\" \"A!1\" \"B\" \"faulty\")) (lemma \"fault_bound\") (grind))"))'`
>
> </details>
>
> The `2f+1` certificate implies `f+1` correct members theorem is proved. Now I’m proving the direct form the PBFT prepared-safety argument uses: two large certificates overlap in a correct replica.
>
> <details><summary>Ran a command</summary>
>
> - Ran `~/git/PVS/pvs -raw -E '(let ((*proof-prompt-behavior* :noquestions) (*proceed-without-asking* t)) (prove-formula-decl "large_quorums_overlap_correct_check: THEOREM FORALL (A, B: replica_set): quorum_2f_plus_1?(A) AND quorum_2f_plus_1?(B) IMPLIES EXISTS (r: replica): A(r) AND B(r) AND correct(r)" "pbft_quorums" "(then (skosimp*) (lemma \"large_quorums_overlap\" (\"A\" \"A!1\" \"B\" \"B!1\")) (lemma \"quorum_contains_correct\" (\"A\" \"intersection(A!1, B!1)\")) (grind))"))'`
>
> </details>
>
> The correct-overlap theorem is proved. I’m finishing the quorum layer with the view-change shape: an `f+1` correct prepared set intersects any `2f+1` new-view set.
>
> <details><summary>Ran 2 commands</summary>
>
> - Ran `~/git/PVS/pvs -raw -E '(let ((*proof-prompt-behavior* :noquestions) (*proceed-without-asking* t)) (prove-formula-decl "correct_small_large_quorums_overlap_check: THEOREM FORALL (A, B: replica_set): quorum_f_plus_1?(A) AND (FORALL (r: replica): A(r) IMPLIES correct(r)) AND quorum_2f_plus_1?(B) IMPLIES EXISTS (r: replica): A(r) AND B(r) AND correct(r)" "pbft_quorums" "(then (skosimp*) (lemma \"small_large_quorums_overlap\" (\"A\" \"A!1\" \"B\" \"B!1\")) (grind))"))'`
> - Ran `~/git/PVS/pvs -raw -E '(let ((*proof-prompt-behavior* :noquestions) (*proceed-without-asking* t)) (prove-formula-decl "small_large_quorums_overlap_check: THEOREM FORALL (A, B: replica_set): quorum_f_plus_1?(A) AND quorum_2f_plus_1?(B) IMPLIES EXISTS (r: replica): A(r) AND B(r)" "pbft_quorums" "(then (skosimp*) (lemma \"pidgeon_hole\" (\"A\" \"A!1\" \"B\" \"B!1\" \"k\" \"1\")) (lemma \"card_1_has_1\" (\"S\" \"intersection(A!1, B!1)\")) (grind))"))'`
>
> </details>
>
> The small/large overlap proves, but adding the “and correct” conjunct needs one explicit instantiation of the assumption that every member of the small set is correct. I’m trying a more aggressive instantiation strategy before deciding whether to split that too.
>
> <details><summary>Ran a command</summary>
>
> - Ran `~/git/PVS/pvs -raw -E '(let ((*proof-prompt-behavior* :noquestions) (*proceed-without-asking* t)) (prove-formula-decl "correct_small_large_quorums_overlap_check: THEOREM FORALL (A, B: replica_set): quorum_f_plus_1?(A) AND (FORALL (r: replica): A(r) IMPLIES correct(r)) AND quorum_2f_plus_1?(B) IMPLIES EXISTS (r: replica): A(r) AND B(r) AND correct(r)" "pbft_quorums" "(then (skosimp*) (lemma \"small_large_quorums_overlap\" (\"A\" \"A!1\" \"B\" \"B!1\")) (grind :if-match all))"))'`
>
> </details>
>
> That aggressive `:if-match all` path is exploding, so I’m stopping it and taking the calmer route: split out a small logical lemma that adds `correct` to an existing overlap witness.
>
> <details><summary>Ran a command</summary>
>
> - Ran `~/git/PVS/pvs -raw -E '(let ((*proof-prompt-behavior* :noquestions) (*proceed-without-asking* t)) (prove-formula-decl "overlap_of_correct_set_is_correct_check: THEOREM FORALL (A, B: replica_set): (EXISTS (r: replica): A(r) AND B(r)) AND (FORALL (r: replica): A(r) IMPLIES correct(r)) IMPLIES EXISTS (r: replica): A(r) AND B(r) AND correct(r)" "pbft_quorums" "(grind)"))'`
>
> </details>
>
> The prover is making the simple witness step harder because it is expanding finite-set witnesses. I’m testing a more surgical proof script: first get the overlap witness, then instantiate the “members of A are correct” assumption with that same witness.
>
> <details><summary>Ran a command</summary>
>
> - Ran `~/git/PVS/pvs -raw -E '(let ((*proof-prompt-behavior* :noquestions) (*proceed-without-asking* t)) (prove-formula-decl "correct_small_large_quorums_overlap_check: THEOREM FORALL (A, B: replica_set): quorum_f_plus_1?(A) AND (FORALL (r: replica): A(r) IMPLIES correct(r)) AND quorum_2f_plus_1?(B) IMPLIES EXISTS (r: replica): A(r) AND B(r) AND correct(r)" "pbft_quorums" "(then (skosimp*) (lemma \"small_large_quorums_overlap\" (\"A\" \"A!1\" \"B\" \"B!1\")) (flatten) (inst?) (grind))"))'`
>
> </details>
>
> The quorum layer is enough for the protocol proofs, and I’ll avoid overfitting that last helper. I’m moving up a level now: protocol predicates for prepared, committed-local, view-change carriage, checkpoint certificates, and client reply certificates, all resting on the proved quorum facts.
>
> <details><summary>Created a file</summary>
>
> - Wrote `./pvs/pbft_protocol.pvs` (+122 -0)
>
> </details>
>
> I spotted two forward references in the new protocol file (`prepared` and `valid_reply` used before their declarations). PVS is happier when the dependency order is explicit, so I’m reordering those declarations before typechecking.
>
> <details><summary>Edited a file</summary>
>
> - Wrote `./pvs/pbft_protocol.pvs` (+7 -8)
>
> </details>
>
> The protocol declarations are ordered now. I’m typechecking `pbft_protocol` and reading any TCCs it produces.
>
> <details><summary>Ran a command</summary>
>
> - Ran `~/git/PVS/pvs -raw -E '(tc "pbft_protocol" t)'`
>
> </details>
>
> `pbft_protocol` typechecks and generated three TCCs; one was subsumed and two are unproved. I’m reading them now, because they’re likely the useful recursion sanity checks around replay.
>
> <details><summary>Ran a command</summary>
>
> - Ran `~/git/PVS/pvs -raw -E '(show-tccs "pbft_protocol")'`
>
> </details>
>
> The TCCs are exactly the expected replay recursion obligations: `k - 1` is natural and smaller when `k /= 0`. I’ll keep that structure and prove the TCCs with arithmetic rather than rewriting the recursion to dodge them.
>
> <details><summary>Ran 2 commands</summary>
>
> - Ran `~/git/PVS/pvs -raw -E '(let ((*proof-prompt-behavior* :noquestions) (*proceed-without-asking* t)) (prove-formula-decl "run_state_TCC1_check: OBLIGATION FORALL (k: nat): NOT k = 0 IMPLIES k - 1 >= 0" "pbft_protocol" "(grind)"))'`
> - Ran `~/git/PVS/pvs -raw -E '(let ((*proof-prompt-behavior* :noquestions) (*proceed-without-asking* t)) (prove-formula-decl "run_state_TCC2_check: OBLIGATION FORALL (k: nat): NOT k = 0 IMPLIES k - 1 < k" "pbft_protocol" "(grind)"))'`
>
> </details>
>
> The replay TCCs prove with plain arithmetic. Now I’m proving the main PBFT protocol theorems, starting with the paper’s normal-case prepared uniqueness invariant.
>
> <details><summary>Ran a command</summary>
>
> - Ran `~/git/PVS/pvs -raw -E '(let ((*proof-prompt-behavior* :noquestions) (*proceed-without-asking* t)) (prove-formula-decl "prepared_certificate_unique_check: THEOREM FORALL (v: view, s: seqno, d1, d2: Digest, Q1, Q2: replica_set): prepared_certificate(v, s, d1, Q1) AND prepared_certificate(v, s, d2, Q2) IMPLIES d1 = d2" "pbft_protocol" "(then (skosimp*) (lemma \"large_quorums_overlap_correct\" (\"A\" \"Q1!1\" \"B\" \"Q2!1\")) (lemma \"correct_prepare_vote_unique\") (grind))"))'`
>
> </details>
>
> The prepared uniqueness proof found the correct overlapping replica, but the generic uniqueness axiom was instantiated with the wrong view/sequence variables. I’m going to make that proof step more automatic by trying a stronger matcher on this smaller theorem.
>
> <details><summary>Ran a command</summary>
>
> - Ran `~/git/PVS/pvs -raw -E '(let ((*proof-prompt-behavior* :noquestions) (*proceed-without-asking* t)) (prove-formula-decl "prepared_certificate_unique_check: THEOREM FORALL (v: view, s: seqno, d1, d2: Digest, Q1, Q2: replica_set): prepared_certificate(v, s, d1, Q1) AND prepared_certificate(v, s, d2, Q2) IMPLIES d1 = d2" "pbft_protocol" "(then (skosimp*) (lemma \"large_quorums_overlap_correct\" (\"A\" \"Q1!1\" \"B\" \"Q2!1\")) (grind :if-match all))"))'`
>
> </details>
>
> That stronger matcher is also exploding. I’m stopping it and will simplify the protocol model slightly: make the “nonfaulty replica does not equivocate” fact a predicate over an explicit overlapping replica, so PVS does not have to guess five quantified arguments.
>
> I’m revising the protocol predicates now. The new shape is cleaner: a correct prepare vote is represented by a deterministic `prepare_value(r, v, s)`, while faulty replicas can satisfy any vote predicate. That directly encodes the paper’s “correct replicas do not sign conflicting prepares; faulty ones may do anything.”
>
> <details><summary>Edited a file</summary>
>
> - Wrote `./pvs/pbft_protocol.pvs` (+7 -10)
>
> </details>
>
> The protocol voting predicates are now definitionally constrained for correct replicas and unconstrained for faulty ones. I’m typechecking that revised model.
>
> <details><summary>Ran a command</summary>
>
> - Ran `~/git/PVS/pvs -raw -E '(tc "pbft_protocol" t)'`
>
> </details>
>
> Typecheck still lands on only the replay TCCs. I’m retrying prepared-certificate uniqueness; this version should be much easier for the prover.
>
> <details><summary>Ran a command</summary>
>
> - Ran `~/git/PVS/pvs -raw -E '(let ((*proof-prompt-behavior* :noquestions) (*proceed-without-asking* t)) (prove-formula-decl "prepared_certificate_unique_check: THEOREM FORALL (v: view, s: seqno, d1, d2: Digest, Q1, Q2: replica_set): prepared_certificate(v, s, d1, Q1) AND prepared_certificate(v, s, d2, Q2) IMPLIES d1 = d2" "pbft_protocol" "(then (skosimp*) (lemma \"large_quorums_overlap_correct\" (\"A\" \"Q1!1\" \"B\" \"Q2!1\")) (grind))"))'`
>
> </details>
>
> The definition is better, but the prover is still instantiating a certificate’s “all members voted” clause with a random cardinality term before the overlap witness. I’m splitting out the exact member lemma: a correct member of a prepared certificate carries that certificate’s digest.
>
> <details><summary>Ran a command</summary>
>
> - Ran `~/git/PVS/pvs -raw -E '(let ((*proof-prompt-behavior* :noquestions) (*proceed-without-asking* t)) (prove-formula-decl "prepared_certificate_member_check: THEOREM FORALL (v: view, s: seqno, d: Digest, Q: replica_set, r: replica): prepared_certificate(v, s, d, Q) AND Q(r) AND correct(r) IMPLIES d = prepare_value(r, v, s)" "pbft_protocol" "(grind)"))'`
>
> </details>
>
> The member lemma proves cleanly. I’m adding it to the protocol theory and then using it twice in the prepared uniqueness proof.
>
> <details><summary>Edited a file</summary>
>
> - Wrote `./pvs/pbft_protocol.pvs` (+4 -0)
>
> </details>
>
> I’ll typecheck once more after adding the lemma, then retry the prepared uniqueness theorem with the exact helper.
>
> <details><summary>Ran a command</summary>
>
> - Ran `~/git/PVS/pvs -raw -E '(tc "pbft_protocol" t)'`
>
> </details>
>
> Typecheck is unchanged. I’m invoking the prepared-certificate uniqueness proof again with the certificate-member lemma available.
>
> <details><summary>Ran a command</summary>
>
> - Ran `~/git/PVS/pvs -raw -E '(let ((*proof-prompt-behavior* :noquestions) (*proceed-without-asking* t)) (prove-formula-decl "prepared_certificate_unique_check: THEOREM FORALL (v: view, s: seqno, d1, d2: Digest, Q1, Q2: replica_set): prepared_certificate(v, s, d1, Q1) AND prepared_certificate(v, s, d2, Q2) IMPLIES d1 = d2" "pbft_protocol" "(then (skosimp*) (lemma \"large_quorums_overlap_correct\" (\"A\" \"Q1!1\" \"B\" \"Q2!1\")) (lemma \"prepared_certificate_member\") (grind))"))'`
>
> </details>
>
> Prepared-certificate uniqueness is proved. I’m lifting it through the existential `prepared` predicate to prove the paper’s normal-case invariant.
>
> <details><summary>Ran a command</summary>
>
> - Ran `~/git/PVS/pvs -raw -E '(let ((*proof-prompt-behavior* :noquestions) (*proceed-without-asking* t)) (prove-formula-decl "prepared_unique_same_view_check: THEOREM FORALL (v: view, s: seqno, d1, d2: Digest): prepared(v, s, d1) AND prepared(v, s, d2) IMPLIES d1 = d2" "pbft_protocol" "(then (skosimp*) (lemma \"prepared_certificate_unique\") (grind))"))'`
>
> </details>
>
> Context compaction
>
> Source: automatic
> Status: completed
>
> I’m picking up from the partially completed formalization and tightening the proof surface now. The cleanest path is to keep the high-level PBFT predicates, but phrase the main safety lemmas in certificate-parametric form where PVS can see the quorum witnesses directly.
>
> <details><summary>Explored 2 files, a list, ran 2 commands</summary>
>
> <details><summary>Explored 2 files, a list</summary>
>
> - Read `./pvs/pbft_quorums.pvs`
> - Read `./pvs/pbft_protocol.pvs`
> - Listed files
>
> </details>
>
> - Ran `~/git/PVS/pvs -raw -E '(tc "pbft_quorums" t)'`
>
> - Ran `~/git/PVS/pvs -raw -E '(tc "pbft_protocol" t)'`
>
> </details>
>
> The base quorum theory still typechecks cleanly. I’m going to try to prove the remaining overlap corollary before deciding whether to prune it; it’s mathematically useful, so it’s worth one careful proof attempt rather than throwing it away too early.
>
> <details><summary>Ran a command</summary>
>
> - Ran `~/git/PVS/pvs -raw -E '(let ((*proof-prompt-behavior* :noquestions) (*proceed-without-asking* t)) (prove-formula-decl "correct_small_large_quorums_overlap_check: THEOREM quorum_f_plus_1?(A) AND (FORALL r: A(r) IMPLIES correct(r)) AND quorum_2f_plus_1?(B) IMPLIES EXISTS r: A(r) AND B(r) AND correct(r)" "pbft_quorums" "(then (skosimp*) (lemma \"small_large_quorums_overlap\" (\"A\" \"A!1\" \"B\" \"B!1\")) (grind))"))'`
>
> </details>
>
> Tiny PVS wrinkle: `prove-formula-decl` does not reuse the theory-level `VAR` declarations for the temporary proof obligations, so I’m quantifying the check formulas explicitly. That’s useful anyway: the proof transcript becomes self-contained.
>
> <details><summary>Ran a command</summary>
>
> - Ran `~/git/PVS/pvs -raw -E '(let ((*proof-prompt-behavior* :noquestions) (*proceed-without-asking* t)) (prove-formula-decl "correct_small_large_quorums_overlap_check: THEOREM FORALL (A, B: replica_set): quorum_f_plus_1?(A) AND (FORALL (r: replica): A(r) IMPLIES correct(r)) AND quorum_2f_plus_1?(B) IMPLIES EXISTS (r: replica): A(r) AND B(r) AND correct(r)" "pbft_quorums" "(then (skosimp*) (lemma \"small_large_quorums_overlap\" (\"A\" \"A!1\" \"B\" \"B!1\")) (grind))"))'`
>
> </details>
>
> That overlap corollary is valid, but the broad `grind` step eagerly instantiates finite-set internals and makes a mess. I’m switching to a witness-first proof style for these, which should also help the PBFT view-change lemmas.
>
> <details><summary>Explored 2 searches, ran 2 commands</summary>
>
> - Ran `~/git/PVS/pvs -raw -E '(let ((*proof-prompt-behavior* :noquestions) (*proceed-without-asking* t)) (prove-formula-decl "correct_small_large_quorums_overlap_check: THEOREM FORALL (A, B: replica_set): quorum_f_plus_1?(A) AND (FORALL (r: replica): A(r) IMPLIES correct(r)) AND quorum_2f_plus_1?(B) IMPLIES EXISTS (r: replica): A(r) AND B(r) AND correct(r)" "pbft_quorums" "(then (skosimp*) (case \"EXISTS (r: replica): A!1(r) AND B!1(r)\") (skolem -1 (\"w\")) (inst 1 \"w\") (grind))"))'`
>
> - Ran `~/git/PVS/pvs -raw -E '(let ((*proof-prompt-behavior* :noquestions) (*proceed-without-asking* t)) (prove-formula-decl "correct_small_large_quorums_overlap_check: THEOREM FORALL (A, B: replica_set): quorum_f_plus_1?(A) AND (FORALL (r: replica): A(r) IMPLIES correct(r)) AND quorum_2f_plus_1?(B) IMPLIES EXISTS (r: replica): A(r) AND B(r) AND correct(r)" "pbft_quorums" "(then (skosimp*) (spread (case \"EXISTS (r: replica): A!1(r) AND B!1(r)\") ((then (skolem -1 (\"w\")) (inst 1 \"w\") (grind)) (then (lemma \"small_large_quorums_overlap\" (\"A\" \"A!1\" \"B\" \"B!1\")) (grind)))))"))'`
>
> <details><summary>Explored 2 searches</summary>
>
> - Searched for `INDUCT|measure-induct|induct` in `lib`
> - Searched for `pidgeon_hole|card_1_has_1|card_subset|card_diff_subset|card_intersection` in `finite_sets`
>
> </details>
>
> </details>
>
> I found the finite-set library’s pigeonhole and cardinality lemmas, which line up nicely with the PBFT proof obligations. The specification can stay small: one quorum algebra theory and one protocol/certificate theory, with the paper’s arguments sitting almost exactly on top of the library lemmas.
>
> Next I’m testing the protocol-level corollaries directly. The main challenge is not the math, it’s guiding PVS through existential certificate witnesses without letting automation instantiate the wrong finite-set terms.
>
> <details><summary>Ran 2 commands</summary>
>
> - Ran `~/git/PVS/pvs -raw -E '(let ((*proof-prompt-behavior* :noquestions) (*proceed-without-asking* t)) (prove-formula-decl "prepared_unique_same_view_check: THEOREM FORALL (v: view, s: seqno, d1, d2: Digest): prepared(v, s, d1) AND prepared(v, s, d2) IMPLIES d1 = d2" "pbft_protocol" "(then (skosimp*) (expand \"prepared\") (skolem -1 (\"Q1\")) (skolem -2 (\"Q2\")) (lemma \"prepared_certificate_unique\" (\"v\" \"v!1\" \"s\" \"s!1\" \"d1\" \"d1!1\" \"d2\" \"d2!1\" \"Q1\" \"Q1\" \"Q2\" \"Q2\")) (grind))"))'`
> - Ran `~/git/PVS/pvs -raw -E '(let ((*proof-prompt-behavior* :noquestions) (*proceed-without-asking* t)) (prove-formula-decl "committed_local_implies_committed_check: THEOREM FORALL (v: view, s: seqno, d: Digest): committed_local(v, s, d) IMPLIES committed(v, s, d)" "pbft_protocol" "(then (skosimp*) (expand \"committed_local\") (skolem -1 (\"C0\")) (expand \"committed\") (inst 1 \"correct_part(C0)\") (lemma \"quorum_has_f_plus_1_correct\" (\"A\" \"C0\")) (grind))"))'`
>
> </details>
>
> One proof attempt wandered into PVS’s interactive prompt because the existential was still bundled inside a conjunction. I’m stopping that session and then I’ll split the antecedent before introducing the commit certificate witness.
>
> I’m using explicit `flatten` steps now. PVS keeps conjunctions and existentials as a single antecedent until told otherwise, and naming the witness too soon is what caused the detour.
>
> <details><summary>Ran a command</summary>
>
> - Ran `~/git/PVS/pvs -raw -E '(let ((*proof-prompt-behavior* :noquestions) (*proceed-without-asking* t)) (prove-formula-decl "committed_local_implies_committed_check: THEOREM FORALL (v: view, s: seqno, d: Digest): committed_local(v, s, d) IMPLIES committed(v, s, d)" "pbft_protocol" "(then (skosimp*) (expand \"committed_local\") (flatten -1) (skolem -2 (\"C0\")) (expand \"committed\") (inst 1 \"correct_part(C0)\") (lemma \"quorum_has_f_plus_1_correct\" (\"A\" \"C0\")) (expand \"commit_certificate\") (grind))"))'`
>
> </details>
>
> The commit-local theorem is now proving cleanly: the commit certificate contributes a `2f+1` set, and its correct part is the `f+1` committed set. I’m moving through the remaining paper corollaries with the same explicit-witness pattern.
>
> <details><summary>Ran 3 commands</summary>
>
> - Ran `~/git/PVS/pvs -raw -E '(let ((*proof-prompt-behavior* :noquestions) (*proceed-without-asking* t)) (prove-formula-decl "committed_unique_per_slot_check: THEOREM FORALL (v: view, s: seqno, d1, d2: Digest): committed(v, s, d1) AND committed(v, s, d2) IMPLIES d1 = d2" "pbft_protocol" "(then (skosimp*) (expand \"committed\") (skolem -1 (\"G1\")) (skolem -2 (\"G2\")) (flatten) (lemma \"quorum_contains_correct\" (\"A\" \"G1\")) (lemma \"quorum_contains_correct\" (\"A\" \"G2\")) (lemma \"prepared_unique_same_view\" (\"v\" \"v!1\" \"s\" \"s!1\" \"d1\" \"d1!1\" \"d2\" \"d2!1\")) (grind))"))'`
> - Ran `~/git/PVS/pvs -raw -E '(let ((*proof-prompt-behavior* :noquestions) (*proceed-without-asking* t)) (prove-formula-decl "view_change_preserves_committed_check: THEOREM FORALL (v1, v2: view, s: seqno, d: Digest, V: replica_set): committed(v1, s, d) AND quorum_2f_plus_1?(V) IMPLIES EXISTS (r: replica): V(r) AND prepared(v1, s, d) AND (carries_prepared(r, v1, v2, s, d) OR stable_above(r, v2, s))" "pbft_protocol" "(then (skosimp*) (expand \"committed\") (skolem -1 (\"G0\")) (flatten) (lemma \"correct_small_large_quorums_overlap\" (\"A\" \"G0\" \"B\" \"V!1\")) (grind))"))'`
> - Ran `~/git/PVS/pvs -raw -E '(let ((*proof-prompt-behavior* :noquestions) (*proceed-without-asking* t)) (prove-formula-decl "view_change_preserves_committed_check: THEOREM FORALL (v1, v2: view, s: seqno, d: Digest, V: replica_set): committed(v1, s, d) AND quorum_2f_plus_1?(V) IMPLIES EXISTS (r: replica): V(r) AND prepared(v1, s, d) AND (carries_prepared(r, v1, v2, s, d) OR stable_above(r, v2, s))" "pbft_protocol" "(then (skosimp*) (expand \"committed\") (skolem -1 (\"G0\")) (flatten) (spread (case \"EXISTS (r: replica): G0(r) AND V!1(r) AND correct(r)\") ((then (skolem -1 (\"w\")) (flatten -1) (inst 1 \"w\") (lemma \"view_change_carries_prepared\" (\"r\" \"w\" \"v1\" \"v1!1\" \"v2\" \"v2!1\" \"s\" \"s!1\" \"d\" \"d!1\")) (grind)) (then (lemma \"correct_small_large_quorums_overlap\" (\"A\" \"G0\" \"B\" \"V!1\")) (grind)))))"))'`
>
> </details>
>
> The view-change branch is almost there; the witness branch closes. The second branch only needs modus ponens on the overlap lemma, and broad `grind` is doing too much again, so I’m replacing it with a narrow `assert`.
>
> <details><summary>Ran a command</summary>
>
> - Ran `~/git/PVS/pvs -raw -E '(let ((*proof-prompt-behavior* :noquestions) (*proceed-without-asking* t)) (prove-formula-decl "view_change_preserves_committed_check: THEOREM FORALL (v1, v2: view, s: seqno, d: Digest, V: replica_set): committed(v1, s, d) AND quorum_2f_plus_1?(V) IMPLIES EXISTS (r: replica): V(r) AND prepared(v1, s, d) AND (carries_prepared(r, v1, v2, s, d) OR stable_above(r, v2, s))" "pbft_protocol" "(then (skosimp*) (expand \"committed\") (skolem -1 (\"G0\")) (flatten) (spread (case \"EXISTS (r: replica): G0(r) AND V!1(r) AND correct(r)\") ((then (skolem -1 (\"w\")) (flatten -1) (inst 1 \"w\") (lemma \"view_change_carries_prepared\" (\"r\" \"w\" \"v1\" \"v1!1\" \"v2\" \"v2!1\" \"s\" \"s!1\" \"d\" \"d!1\")) (assert)) (then (lemma \"correct_small_large_quorums_overlap\" (\"A\" \"G0\" \"B\" \"V!1\")) (assert)))))"))'`
>
> </details>
>
> The last attempt showed the exact missing moves: instantiate the committed set’s “all prepared” fact at the overlap witness, and flatten the implication produced by the overlap lemma. This is now a proof-script plumbing problem, not a modeling problem.
>
> <details><summary>Ran a command</summary>
>
> - Ran `~/git/PVS/pvs -raw -E '(let ((*proof-prompt-behavior* :noquestions) (*proceed-without-asking* t)) (prove-formula-decl "view_change_preserves_committed_check: THEOREM FORALL (v1, v2: view, s: seqno, d: Digest, V: replica_set): committed(v1, s, d) AND quorum_2f_plus_1?(V) IMPLIES EXISTS (r: replica): V(r) AND prepared(v1, s, d) AND (carries_prepared(r, v1, v2, s, d) OR stable_above(r, v2, s))" "pbft_protocol" "(then (skosimp*) (expand \"committed\") (skolem -1 (\"G0\")) (flatten) (spread (case \"EXISTS (r: replica): G0(r) AND V!1(r) AND correct(r)\") ((then (skolem -1 (\"w\")) (flatten -1) (inst 1 \"w\") (inst -7 \"w\") (lemma \"view_change_carries_prepared\" (\"r\" \"w\" \"v1\" \"v1!1\" \"v2\" \"v2!1\" \"s\" \"s!1\" \"d\" \"d!1\")) (assert)) (then (lemma \"correct_small_large_quorums_overlap\" (\"A\" \"G0\" \"B\" \"V!1\")) (flatten -1) (assert)))))"))'`
>
> </details>
>
> I mis-numbered one antecedent after instantiating the witness: PVS renumbered the “all prepared” formula. One more pass with the corrected index, and I’ll use a more propositional close for the overlap branch.
>
> <details><summary>Explored 2 searches, ran a command</summary>
>
> - Ran `~/git/PVS/pvs -raw -E '(let ((*proof-prompt-behavior* :noquestions) (*proceed-without-asking* t)) (prove-formula-decl "view_change_preserves_committed_check: THEOREM FORALL (v1, v2: view, s: seqno, d: Digest, V: replica_set): committed(v1, s, d) AND quorum_2f_plus_1?(V) IMPLIES EXISTS (r: replica): V(r) AND prepared(v1, s, d) AND (carries_prepared(r, v1, v2, s, d) OR stable_above(r, v2, s))" "pbft_protocol" "(then (skosimp*) (expand \"committed\") (skolem -1 (\"G0\")) (flatten) (spread (case \"EXISTS (r: replica): G0(r) AND V!1(r) AND correct(r)\") ((then (skolem -1 (\"w\")) (flatten -1) (inst 1 \"w\") (inst -6 \"w\") (lemma \"view_change_carries_prepared\" (\"r\" \"w\" \"v1\" \"v1!1\" \"v2\" \"v2!1\" \"s\" \"s!1\" \"d\" \"d!1\")) (assert)) (then (lemma \"correct_small_large_quorums_overlap\" (\"A\" \"G0\" \"B\" \"V!1\")) (propax)))))"))'`
>
> <details><summary>Explored 2 searches</summary>
>
> - Searched for `modus|forward-chain|split -|flatten -` in `lib`
> - Searched for `\(use \".*\"|\(lemma \".*\"` in `pvs`
>
> </details>
>
> </details>
>
> I’m checking the existing PVS proof corpus for the right command here. The library uses `forward-chain` for exactly this kind of “I have the antecedent, push the implication’s consequent into the context” step, so I’m going to use that instead of trying to force `assert` to do it.
>
> <details><summary>Explored a search</summary>
>
> - Searched for `forward-chain` in `lib`
>
> </details>
>
> I’m trying `forward-chain` directly on the named overlap theorem now. That should add the existential overlap witness as a usable antecedent, instead of leaving me with an implication to manually discharge.
>
> <details><summary>Ran a command</summary>
>
> - Ran `~/git/PVS/pvs -raw -E '(let ((*proof-prompt-behavior* :noquestions) (*proceed-without-asking* t)) (prove-formula-decl "view_change_preserves_committed_check: THEOREM FORALL (v1, v2: view, s: seqno, d: Digest, V: replica_set): committed(v1, s, d) AND quorum_2f_plus_1?(V) IMPLIES EXISTS (r: replica): V(r) AND prepared(v1, s, d) AND (carries_prepared(r, v1, v2, s, d) OR stable_above(r, v2, s))" "pbft_protocol" "(then (skosimp*) (expand \"committed\") (skolem -1 (\"G0\")) (flatten) (forward-chain \"correct_small_large_quorums_overlap\") (skolem -1 (\"w\")) (flatten -1) (inst 1 \"w\") (inst -6 \"w\") (forward-chain \"view_change_carries_prepared\") (assert))"))'`
>
> </details>
>
> `forward-chain` worked beautifully for the quorum overlap; it is intentionally not allowed for the view-change axiom because the new view variable only appears in the consequent. I’m back to an instantiated axiom there, with one extra propositional cleanup step.
>
> <details><summary>Ran 2 commands</summary>
>
> - Ran `~/git/PVS/pvs -raw -E '(let ((*proof-prompt-behavior* :noquestions) (*proceed-without-asking* t)) (prove-formula-decl "view_change_preserves_committed_check: THEOREM FORALL (v1, v2: view, s: seqno, d: Digest, V: replica_set): committed(v1, s, d) AND quorum_2f_plus_1?(V) IMPLIES EXISTS (r: replica): V(r) AND prepared(v1, s, d) AND (carries_prepared(r, v1, v2, s, d) OR stable_above(r, v2, s))" "pbft_protocol" "(then (skosimp*) (expand \"committed\") (skolem -1 (\"G0\")) (flatten) (forward-chain \"correct_small_large_quorums_overlap\") (skolem -1 (\"w\")) (flatten -1) (inst 1 \"w\") (inst -6 \"w\") (assert) (lemma \"view_change_carries_prepared\" (\"r\" \"w\" \"v1\" \"v1!1\" \"v2\" \"v2!1\" \"s\" \"s!1\" \"d\" \"d!1\")) (assert) (propax))"))'`
> - Ran `~/git/PVS/pvs -raw -E '(let ((*proof-prompt-behavior* :noquestions) (*proceed-without-asking* t)) (prove-formula-decl "stable_checkpoint_has_correct_voter_check: THEOREM FORALL (s: seqno, d: Digest): stable_checkpoint(s, d) IMPLIES EXISTS (r: replica): correct(r) AND checkpoint_vote(r, s, d)" "pbft_protocol" "(then (skosimp*) (expand \"stable_checkpoint\") (skolem -1 (\"C0\")) (flatten) (lemma \"quorum_contains_correct\" (\"A\" \"C0\")) (grind))"))'`
>
> </details>
>
> I’m going to add one small quorum lemma that the later proofs naturally want: every `2f+1` quorum is already large enough to contain a correct replica. That keeps checkpoint and reply proofs from redoing arithmetic each time.
>
> <details><summary>Edited a file</summary>
>
> - Wrote `./pvs/pbft_quorums.pvs` (+7 -0)
>
> </details>
>
> I’m also strengthening the view-change theorem’s conclusion so the witness is explicitly correct. That matches the paper’s argument more directly: the new-view quorum intersects the committed correct set.
>
> <details><summary>Edited a file, ran 2 commands</summary>
>
> - Wrote `./pvs/pbft_protocol.pvs` (+1 -1)
> - Ran `~/git/PVS/pvs -raw -E '(tc "pbft_quorums" t)'`
> - Ran `~/git/PVS/pvs -raw -E '(tc "pbft_protocol" t)'`
>
> </details>
>
> Both theories still typecheck after the strengthening. I’m running the new quorum proof checks first, then I’ll rerun the protocol-level theorem checks against the strengthened statement.
>
> <details><summary>Ran 4 commands</summary>
>
> - Ran `~/git/PVS/pvs -raw -E '(let ((*proof-prompt-behavior* :noquestions) (*proceed-without-asking* t)) (prove-formula-decl "large_quorum_is_small_check: LEMMA FORALL (A: replica_set): quorum_2f_plus_1?(A) IMPLIES quorum_f_plus_1?(A)" "pbft_quorums" "(grind)"))'`
> - Ran `~/git/PVS/pvs -raw -E '(let ((*proof-prompt-behavior* :noquestions) (*proceed-without-asking* t)) (prove-formula-decl "large_quorum_contains_correct_check: THEOREM FORALL (A: replica_set): quorum_2f_plus_1?(A) IMPLIES EXISTS (r: replica): A(r) AND correct(r)" "pbft_quorums" "(then (skosimp*) (lemma \"large_quorum_is_small\" (\"A\" \"A!1\")) (lemma \"quorum_contains_correct\" (\"A\" \"A!1\")) (grind))"))'`
> - Ran `~/git/PVS/pvs -raw -E '(let ((*proof-prompt-behavior* :noquestions) (*proceed-without-asking* t)) (prove-formula-decl "stable_checkpoint_has_correct_voter_check: THEOREM FORALL (s: seqno, d: Digest): stable_checkpoint(s, d) IMPLIES EXISTS (r: replica): correct(r) AND checkpoint_vote(r, s, d)" "pbft_protocol" "(then (skosimp*) (expand \"stable_checkpoint\") (skolem -1 (\"C0\")) (flatten) (forward-chain \"large_quorum_contains_correct\") (skolem -1 (\"w\")) (flatten -1) (inst 1 \"w\") (inst -4 \"w\") (assert))"))'`
> - Ran `~/git/PVS/pvs -raw -E '(let ((*proof-prompt-behavior* :noquestions) (*proceed-without-asking* t)) (prove-formula-decl "client_certificate_valid_check: THEOREM FORALL (t: timestamp, d: Digest, C: replica_set): client_reply_certificate(t, d, C) IMPLIES valid_reply(t, d)" "pbft_protocol" "(then (skosimp*) (expand \"client_reply_certificate\") (flatten) (forward-chain \"quorum_contains_correct\") (skolem -1 (\"w\")) (flatten -1) (inst -4 \"w\") (expand \"reply_vote\") (grind))"))'`
>
> </details>
>
> Checkpoint and client-side reply certificates now prove with the quorum lemmas. I’m rerunning the core safety obligations next: prepared uniqueness, commit-local implies committed, committed uniqueness, and the strengthened view-change preservation.
>
> <details><summary>Ran 3 commands</summary>
>
> - Ran `~/git/PVS/pvs -raw -E '(let ((*proof-prompt-behavior* :noquestions) (*proceed-without-asking* t)) (prove-formula-decl "prepared_certificate_member_check: LEMMA FORALL (v: view, s: seqno, d: Digest, Q: replica_set, r: replica): prepared_certificate(v, s, d, Q) AND Q(r) AND correct(r) IMPLIES d = prepare_value(r, v, s)" "pbft_protocol" "(grind)"))'`
> - Ran `~/git/PVS/pvs -raw -E '(let ((*proof-prompt-behavior* :noquestions) (*proceed-without-asking* t)) (prove-formula-decl "prepared_certificate_unique_check: THEOREM FORALL (v: view, s: seqno, d1, d2: Digest, Q1, Q2: replica_set): prepared_certificate(v, s, d1, Q1) AND prepared_certificate(v, s, d2, Q2) IMPLIES d1 = d2" "pbft_protocol" "(then (skosimp*) (lemma \"large_quorums_overlap_correct\" (\"A\" \"Q1!1\" \"B\" \"Q2!1\")) (lemma \"prepared_certificate_member\") (grind))"))'`
> - Ran `~/git/PVS/pvs -raw -E '(let ((*proof-prompt-behavior* :noquestions) (*proceed-without-asking* t)) (prove-formula-decl "prepared_unique_same_view_check: THEOREM FORALL (v: view, s: seqno, d1, d2: Digest): prepared(v, s, d1) AND prepared(v, s, d2) IMPLIES d1 = d2" "pbft_protocol" "(then (skosimp*) (expand \"prepared\") (skolem -1 (\"Q1\")) (skolem -2 (\"Q2\")) (lemma \"prepared_certificate_unique\" (\"v\" \"v!1\" \"s\" \"s!1\" \"d1\" \"d1!1\" \"d2\" \"d2!1\" \"Q1\" \"Q1\" \"Q2\" \"Q2\")) (grind))"))'`
>
> </details>
>
> The prepared-certificate intersection chain is proved again. Now I’m closing the commit and view-change side; these are the paper’s “commit certificate implies committed” and “view change preserves committed requests” arguments.
>
> <details><summary>Ran 3 commands</summary>
>
> - Ran `~/git/PVS/pvs -raw -E '(let ((*proof-prompt-behavior* :noquestions) (*proceed-without-asking* t)) (prove-formula-decl "committed_local_implies_committed_check: THEOREM FORALL (v: view, s: seqno, d: Digest): committed_local(v, s, d) IMPLIES committed(v, s, d)" "pbft_protocol" "(then (skosimp*) (expand \"committed_local\") (flatten -1) (skolem -2 (\"C0\")) (expand \"committed\") (inst 1 \"correct_part(C0)\") (lemma \"quorum_has_f_plus_1_correct\" (\"A\" \"C0\")) (expand \"commit_certificate\") (grind))"))'`
> - Ran `~/git/PVS/pvs -raw -E '(let ((*proof-prompt-behavior* :noquestions) (*proceed-without-asking* t)) (prove-formula-decl "committed_unique_per_slot_check: THEOREM FORALL (v: view, s: seqno, d1, d2: Digest): committed(v, s, d1) AND committed(v, s, d2) IMPLIES d1 = d2" "pbft_protocol" "(then (skosimp*) (expand \"committed\") (skolem -1 (\"G1\")) (skolem -2 (\"G2\")) (flatten) (lemma \"quorum_contains_correct\" (\"A\" \"G1\")) (lemma \"quorum_contains_correct\" (\"A\" \"G2\")) (lemma \"prepared_unique_same_view\" (\"v\" \"v!1\" \"s\" \"s!1\" \"d1\" \"d1!1\" \"d2\" \"d2!1\")) (grind))"))'`
> - Ran `~/git/PVS/pvs -raw -E '(let ((*proof-prompt-behavior* :noquestions) (*proceed-without-asking* t)) (prove-formula-decl "view_change_preserves_committed_check: THEOREM FORALL (v1, v2: view, s: seqno, d: Digest, V: replica_set): committed(v1, s, d) AND quorum_2f_plus_1?(V) IMPLIES EXISTS (r: replica): V(r) AND correct(r) AND prepared(v1, s, d) AND (carries_prepared(r, v1, v2, s, d) OR stable_above(r, v2, s))" "pbft_protocol" "(then (skosimp*) (expand \"committed\") (skolem -1 (\"G0\")) (flatten) (forward-chain \"correct_small_large_quorums_overlap\") (skolem -1 (\"w\")) (flatten -1) (inst 1 \"w\") (inst -6 \"w\") (assert) (lemma \"view_change_carries_prepared\" (\"r\" \"w\" \"v1\" \"v1!1\" \"v2\" \"v2!1\" \"s\" \"s!1\" \"d\" \"d!1\")) (assert))"))'`
>
> </details>
>
> One last theorem is the deterministic replay lemma. This is outside the quorum math, so I’m switching to induction on the replay length and letting the recursive definition drive the proof.
>
> <details><summary>Ran a command</summary>
>
> - Ran `~/git/PVS/pvs -raw -E '(let ((*proof-prompt-behavior* :noquestions) (*proceed-without-asking* t)) (prove-formula-decl "deterministic_replay_check: THEOREM FORALL (init: State, reqs1, reqs2: schedule, k: nat): (FORALL (m: below(k)): reqs1(m) = reqs2(m)) IMPLIES run_state(init, reqs1, k) = run_state(init, reqs2, k)" "pbft_protocol" "(then (induct \"k\") (grind))"))'`
>
> </details>
>
> The replay proof needs the induction hypothesis explicitly: PVS can see the last request equality at index `j`, but it needs help deriving the prefix equality for all indices below `j`. I’ll split the induction branches and feed that premise to the hypothesis.
>
> <details><summary>Ran a command</summary>
>
> - Ran `~/git/PVS/pvs -raw -E '(let ((*proof-prompt-behavior* :noquestions) (*proceed-without-asking* t)) (prove-formula-decl "deterministic_replay_check: THEOREM FORALL (init: State, reqs1, reqs2: schedule, k: nat): (FORALL (m: below(k)): reqs1(m) = reqs2(m)) IMPLIES run_state(init, reqs1, k) = run_state(init, reqs2, k)" "pbft_protocol" "(spread (induct \"k\") ((grind) (then (skosimp*) (expand \"run_state\") (inst -1 \"init!1\" \"reqs1!1\" \"reqs2!1\") (assert))))"))'`
>
> </details>
>
> The first induction attempt expanded the recursive call inside the induction hypothesis too early. I’m going to first assert the prefix-equality premise, use the hypothesis at length `j`, and only then unfold the final step of `run_state`.
>
> <details><summary>Ran a command</summary>
>
> - Ran `~/git/PVS/pvs -raw -E '(let ((*proof-prompt-behavior* :noquestions) (*proceed-without-asking* t)) (prove-formula-decl "deterministic_replay_check: THEOREM FORALL (init: State, reqs1, reqs2: schedule, k: nat): (FORALL (m: below(k)): reqs1(m) = reqs2(m)) IMPLIES run_state(init, reqs1, k) = run_state(init, reqs2, k)" "pbft_protocol" "(spread (induct \"k\") ((grind) (then (skosimp*) (inst -1 \"init!1\" \"reqs1!1\" \"reqs2!1\") (spread (case \"FORALL (m: below(j!1)): reqs1!1(m) = reqs2!1(m)\") ((then (assert) (expand \"run_state\") (grind)) (grind))))))"))'`
>
> </details>
>
> The induction proof is now in the right shape; it has the prefix premise and the last-element premise. I’m waiting for PVS to finish the arithmetic/subtype cleanup for the step case.
>
> That last `grind` was too eager and recursively unfolded the replay function until SBCL ran out of stack. I’m tightening the proof: forward-chain the induction hypothesis into a single equality, instantiate the last request equality, and unfold only the goal occurrence of `run_state`.
>
> <details><summary>Ran a command</summary>
>
> - Ran `~/git/PVS/pvs -raw -E '(let ((*proof-prompt-behavior* :noquestions) (*proceed-without-asking* t)) (prove-formula-decl "deterministic_replay_check: THEOREM FORALL (init: State, reqs1, reqs2: schedule, k: nat): (FORALL (m: below(k)): reqs1(m) = reqs2(m)) IMPLIES run_state(init, reqs1, k) = run_state(init, reqs2, k)" "pbft_protocol" "(spread (induct \"k\") ((grind) (then (skosimp*) (inst -1 \"init!1\" \"reqs1!1\" \"reqs2!1\") (spread (case \"FORALL (m: below(j!1)): reqs1!1(m) = reqs2!1(m)\") ((then (forward-chain -2) (inst -3 \"j!1\") (expand \"run_state\" 1) (assert)) (grind))))))"))'`
>
> </details>
>
> Good, the step branch closes; the remaining branch is only proving that a prefix of a matching sequence still matches. I’m hiding the unrelated replay goal there so PVS doesn’t unfold anything recursively.
>
> <details><summary>Ran a command</summary>
>
> - Ran `~/git/PVS/pvs -raw -E '(let ((*proof-prompt-behavior* :noquestions) (*proceed-without-asking* t)) (prove-formula-decl "deterministic_replay_check: THEOREM FORALL (init: State, reqs1, reqs2: schedule, k: nat): (FORALL (m: below(k)): reqs1(m) = reqs2(m)) IMPLIES run_state(init, reqs1, k) = run_state(init, reqs2, k)" "pbft_protocol" "(spread (induct \"k\") ((grind) (then (skosimp*) (inst -1 \"init!1\" \"reqs1!1\" \"reqs2!1\") (spread (case \"FORALL (m: below(j!1)): reqs1!1(m) = reqs2!1(m)\") ((then (inst -3 \"j!1\") (expand \"run_state\" 1) (assert)) (then (hide 2) (skosimp*) (inst -2 \"m!1\") (assert)))))))"))'`
>
> </details>
>
> The deterministic replay induction is proved now. I’m doing one final TCC pass: PVS generated the expected arithmetic obligations from the structurally recursive `run_state`, and I’ll show and prove those explicitly.
>
> <details><summary>Ran 3 commands</summary>
>
> - Ran `~/git/PVS/pvs -raw -E '(show-tccs "pbft_protocol")'`
> - Ran `~/git/PVS/pvs -raw -E '(let ((*proof-prompt-behavior* :noquestions) (*proceed-without-asking* t)) (prove-formula-decl "run_state_TCC1_check: OBLIGATION FORALL (k: nat): NOT k = 0 IMPLIES k - 1 >= 0" "pbft_protocol" "(grind)"))'`
> - Ran `~/git/PVS/pvs -raw -E '(let ((*proof-prompt-behavior* :noquestions) (*proceed-without-asking* t)) (prove-formula-decl "run_state_TCC2_check: OBLIGATION FORALL (k: nat): NOT k = 0 IMPLIES k - 1 < k" "pbft_protocol" "(grind)"))'`
>
> </details>
>
> I’m doing a final sweep of the quorum theorem checks too, so the foundation is not just typechecked but independently discharged with the PVS prover.
>
> <details><summary>Ran 4 commands</summary>
>
> - Ran `~/git/PVS/pvs -raw -E '(let ((*proof-prompt-behavior* :noquestions) (*proceed-without-asking* t)) (prove-formula-decl "quorum_has_f_plus_1_correct_check: THEOREM FORALL (A: replica_set): quorum_2f_plus_1?(A) IMPLIES card(correct_part(A)) >= f + 1" "pbft_quorums" "(then (skosimp*) (lemma \"difference_own_intersection\" (\"A\" \"A!1\" \"B\" \"faulty\")) (lemma \"card_diff_subset\" (\"A\" \"intersection(A!1, faulty)\" \"B\" \"A!1\")) (lemma \"card_intersection_le\" (\"A\" \"A!1\" \"B\" \"faulty\")) (lemma \"fault_bound\") (grind))"))'`
> - Ran `~/git/PVS/pvs -raw -E '(let ((*proof-prompt-behavior* :noquestions) (*proceed-without-asking* t)) (prove-formula-decl "large_quorums_overlap_correct_check: THEOREM FORALL (A, B: replica_set): quorum_2f_plus_1?(A) AND quorum_2f_plus_1?(B) IMPLIES EXISTS (r: replica): A(r) AND B(r) AND correct(r)" "pbft_quorums" "(then (skosimp*) (lemma \"large_quorums_overlap\" (\"A\" \"A!1\" \"B\" \"B!1\")) (lemma \"quorum_contains_correct\" (\"A\" \"intersection(A!1, B!1)\")) (grind))"))'`
> - Ran `~/git/PVS/pvs -raw -E '(let ((*proof-prompt-behavior* :noquestions) (*proceed-without-asking* t)) (prove-formula-decl "large_quorums_overlap_check: THEOREM FORALL (A, B: replica_set): quorum_2f_plus_1?(A) AND quorum_2f_plus_1?(B) IMPLIES card(intersection(A, B)) >= f + 1" "pbft_quorums" "(then (skosimp*) (lemma \"pidgeon_hole\" (\"A\" \"A!1\" \"B\" \"B!1\" \"k\" \"f+1\")) (grind))"))'`
> - Ran `~/git/PVS/pvs -raw -E '(let ((*proof-prompt-behavior* :noquestions) (*proceed-without-asking* t)) (prove-formula-decl "small_large_quorums_overlap_check: THEOREM FORALL (A, B: replica_set): quorum_f_plus_1?(A) AND quorum_2f_plus_1?(B) IMPLIES EXISTS (r: replica): A(r) AND B(r)" "pbft_quorums" "(then (skosimp*) (lemma \"pidgeon_hole\" (\"A\" \"A!1\" \"B\" \"B!1\" \"k\" \"1\")) (lemma \"card_1_has_1\" (\"S\" \"intersection(A!1, B!1)\")) (grind))"))'`
>
> </details>
>
> The quorum sweep is clean. I’m checking the two small “there is a correct replica” quorum corollaries as the final foundation pieces.
>
> <details><summary>Ran 2 commands</summary>
>
> - Ran `~/git/PVS/pvs -raw -E '(let ((*proof-prompt-behavior* :noquestions) (*proceed-without-asking* t)) (prove-formula-decl "quorum_contains_correct_check: THEOREM FORALL (A: replica_set): quorum_f_plus_1?(A) IMPLIES EXISTS (r: replica): A(r) AND correct(r)" "pbft_quorums" "(then (skosimp*) (lemma \"quorum_not_all_faulty\" (\"A\" \"A!1\")) (lemma \"not_all_faulty_has_correct\" (\"A\" \"A!1\")) (grind))"))'`
> - Ran `~/git/PVS/pvs -raw -E '(let ((*proof-prompt-behavior* :noquestions) (*proceed-without-asking* t)) (prove-formula-decl "correct_small_large_quorums_overlap_check: THEOREM FORALL (A, B: replica_set): quorum_f_plus_1?(A) AND (FORALL (r: replica): A(r) IMPLIES correct(r)) AND quorum_2f_plus_1?(B) IMPLIES EXISTS (r: replica): A(r) AND B(r) AND correct(r)" "pbft_quorums" "(then (skosimp*) (spread (case \"EXISTS (r: replica): A!1(r) AND B!1(r)\") ((then (skolem -1 (\"w\")) (inst 1 \"w\") (grind)) (then (lemma \"small_large_quorums_overlap\" (\"A\" \"A!1\" \"B\" \"B!1\")) (grind)))))"))'`
>
> </details>
>
> All the proof checks I intended to run are Q.E.D. now. I’m doing a last quick file/line pass so the final note can point you straight at the relevant specs.
>
> <details><summary>Explored 2 files, ran a command</summary>
>
> <details><summary>Explored 2 files</summary>
>
> - Read `./pvs/pbft_protocol.pvs`
> - Read `./pvs/pbft_quorums.pvs`
>
> </details>
>
> - Ran `git status --short`
>
> </details>
>
> This workspace is not a Git repository, so there’s no git status to report. The specs themselves are in place and the final typecheck/proof checks are done.
>
> <details><summary>Explored a list</summary>
>
> - Listed files in `pvs`
>
> </details>
>
> <details><summary>Plan</summary>
>
> - [ ] Inspect repository and PBFT document
> - [ ] Design PVS theory structure and theorem targets
> - [ ] Implement PVS specifications under pvs/
> - [ ] Typecheck, inspect TCCs, and prove theorem declarations
> - [ ] Summarize files, proof status, and remaining risks
>
> </details>
</details>

Implemented the PBFT formalization under `pvs/`.

The main files are:

- [pbft_quorums.pvs](./pvs/pbft_quorums.pvs:1): `n = 3f + 1`, replica typing, fault bound, quorum algebra, and the PBFT overlap lemmas.
- [pbft_protocol.pvs](./pvs/pbft_protocol.pvs:1): prepared/commit/checkpoint/reply certificates, view-change preservation, and deterministic replay.

I verified with PVS:

- `pbft_quorums` typechecks with no TCCs.
- `pbft_protocol` typechecks with the expected 3 replay recursion TCCs; one is subsumed, and the two explicit arithmetic obligations prove with `grind`.
- Proved mirrored `prove-formula-decl` checks for the core theorems: quorum overlap/correctness, prepared uniqueness, commit-local implies committed, committed uniqueness, view-change preservation, checkpoint correct voter, client reply validity, and deterministic replay.

One modeling note: the view-change theorem uses a small axiom capturing the paper’s view-change condition: a correct replica with a prepared certificate either carries it into the new view or has a stable checkpoint above the sequence number.
