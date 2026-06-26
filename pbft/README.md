# PBFT Formalization in PVS (Codex/GPT5.5)

## Proof Status

```
 Proof summary for theory pbft_protocol
    prepared_certificate_member...........proved - complete   [SHOSTAK](0.00 s)
    prepared_certificate_unique...........proved - incomplete [SHOSTAK](0.00 s)
    prepared_unique_same_view.............proved - incomplete [SHOSTAK](0.00 s)
    committed_local_implies_committed.....proved - complete   [SHOSTAK](0.00 s)
    committed_unique_per_slot.............proved - incomplete [SHOSTAK](0.00 s)
    view_change_preserves_committed.......proved - incomplete [SHOSTAK](0.00 s)
    stable_checkpoint_has_correct_voter...proved - complete   [SHOSTAK](0.00 s)
    client_certificate_valid..............proved - complete   [SHOSTAK](0.00 s)
    run_state_TCC1........................proved - complete   [SHOSTAK](0.00 s)
    run_state_TCC2........................proved - complete   [SHOSTAK](0.00 s)
    deterministic_replay..................proved - complete   [SHOSTAK](0.00 s)
    Theory pbft_protocol totals: 11 formulas, 11 attempted, 11 succeeded (0.00 s)

 Proof summary for theory pbft_quorums
    replica_is_finite_type................proved - complete   [SHOSTAK](0.00 s)
    difference_own_intersection...........proved - complete   [SHOSTAK](0.00 s)
    one_more_than_faults_is_positive......proved - complete   [SHOSTAK](0.00 s)
    all_faulty_card_bound.................proved - complete   [SHOSTAK](0.00 s)
    quorum_not_all_faulty.................proved - complete   [SHOSTAK](0.00 s)
    not_all_faulty_has_correct............proved - complete   [SHOSTAK](0.00 s)
    quorum_contains_correct...............proved - complete   [SHOSTAK](0.00 s)
    large_quorum_is_small.................proved - complete   [SHOSTAK](0.00 s)
    large_quorum_contains_correct.........proved - complete   [SHOSTAK](0.00 s)
    quorum_has_f_plus_1_correct...........proved - complete   [SHOSTAK](0.00 s)
    large_quorums_overlap.................proved - incomplete [SHOSTAK](0.00 s)
    large_quorums_overlap_correct.........proved - incomplete [SHOSTAK](0.00 s)
    small_large_quorums_overlap...........proved - incomplete [SHOSTAK](0.00 s)
    correct_small_large_quorums_overlap...proved - incomplete [SHOSTAK](0.00 s)
    Theory pbft_quorums totals: 14 formulas, 14 attempted, 14 succeeded (0.00 s)

 Proof summary for theory top
    Theory top totals: 0 formulas, 0 attempted, 0 succeeded (0.00 s)

Grand Totals: 25 proofs, 25 attempted, 25 succeeded (0.00 s)
```
