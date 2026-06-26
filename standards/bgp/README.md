# RFC 4271 BGP-4 SAL Model Checking

Source modeled: RFC 4271, "A Border Gateway Protocol 4 (BGP-4)", from
`https://datatracker.ietf.org/doc/html/rfc4271`.

Local source copy: `rfc4271.txt` (`5827` lines).

SAL model: `bgp4_rfc4271.sal` (`1794` lines).

## Scope

The model is an executable finite-state abstraction of the base RFC 4271
protocol.  It covers:

- Section 3: TCP transport, port 179, route advertisement/storage, RIBs.
- Section 4: BGP message header, OPEN, UPDATE, KEEPALIVE, NOTIFICATION.
- Section 5: path-attribute recognition, propagation, AS_PATH, NEXT_HOP,
  MULTI_EXIT_DISC, LOCAL_PREF, ATOMIC_AGGREGATE, AGGREGATOR.
- Section 6: header, OPEN, UPDATE, hold-timer, FSM, Cease, and collision
  error handling.
- Section 7: version-negotiation format preservation.
- Section 8: peer FSM states and important state transitions.
- Section 9: UPDATE handling, Decision Process phases, route dissemination,
  route advertisement rate limiting, overlapping routes, aggregation.
- Section 10: timer configurability and jitter.
- Appendix E and Security Considerations: TCP MD5 support.

The model intentionally abstracts concrete byte strings, IPv4 addresses,
prefix sets, AS_PATH tuple lists, timer durations, TCP streams, and policy
databases into finite predicates.  It models one peer session and one abstract
NLRI equivalence class, which is enough for the RFC's local safety obligations.

## Theorem Inventory

The SAL file contains `107` labeled requirements/lemmas, all named with the
`req_` prefix and grouped under comments citing the relevant RFC section and
local source-line range.

Coverage summary:

- `req_s3_*`: 6 requirements.
- `req_s4_*`: 14 requirements.
- `req_s5_*`: 21 requirements.
- `req_s6_*`: 31 requirements.
- `req_s7_*`: 1 requirement.
- `req_s8_*`: 10 requirements.
- `req_s9_*`: 20 requirements.
- `req_s10_*`: 2 requirements.
- `req_app_e_*` / `req_security_*`: 2 requirements.

## Commands Run

Well-formedness/typechecking:

```sh
sal-wfc bgp4_rfc4271.sal
```

Result:

```text
Ok.
```

Requirement model checking with infinite-state bounded model checking plus
k-induction:

```sh
fail=0; total=0
for t in $(rg --pcre2 -o 'req_[A-Za-z0-9_]+(?=: THEOREM)' bgp4_rfc4271.sal); do
  total=$((total+1))
  out=$(sal-inf-bmc --depth=3 --induction bgp4_rfc4271 "$t" 2>&1)
  if printf '%s\n' "$out" | rg -q '^proved\.$'; then
    printf 'OK %s\n' "$t"
  else
    fail=$((fail+1))
    printf 'FAIL %s :: ' "$t"
    printf '%s\n' "$out" | head -n 1
  fi
done
printf 'TOTAL=%s FAIL=%s\n' "$total" "$fail"
```

Final result:

```text
TOTAL=107 FAIL=0
```

## Notes

- The RFC has later updates, but this artifact targets RFC 4271 as written.
- The proof obligations are safety properties over the abstract transition
  system.  They do not prove byte-level parser correctness, timing precision,
  cryptographic strength, or global Internet convergence.
- Error cases that RFC 4271 says should be logged/ignored without closing the
  connection are modeled separately from fatal UPDATE errors that send
  NOTIFICATION and close the connection.
