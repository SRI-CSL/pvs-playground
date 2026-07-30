# RFC 9200 ACE-OAuth SAL Model Check

Model: `ace_oauth_rfc9200.sal`

SAL used:

```sh
sal-wfc ace_oauth_rfc9200.sal

for a in $(rg -o '^  req_[A-Za-z0-9_]+' ace_oauth_rfc9200.sal | sed 's/^  //'); do
  sal-inf-bmc --depth=3 --induction ace_oauth_rfc9200.sal "$a"
done
```

Results:

- `sal-wfc`: `Ok.`
- `sal-inf-bmc --depth=3 --induction`: all 68 named `req_*` assertions proved.

Model scope:

- ACE roles: client, resource server, authorization server.
- Discovery and AS Request Creation Hints, including `cnonce`.
- Client and RS registration with the AS.
- Profile obligations for C-RS, C-AS, and RS-AS communication.
- Token endpoint behavior, including default grant handling, PoP token defaults, CBOR mappings, profile return, and ACE-specific token errors.
- Refresh token constraints for same PoP key, same audience, and no broader scope.
- Introspection endpoint behavior, including active/inactive responses and error handling.
- `authz-info` token posting and RS token verification.
- Protected-resource access decisions and response codes.
- Token expiration, `exi`/`cti`, key-expiration handling, and long-running requests.
- Security considerations for token integrity, encrypted symmetric PoP keys, multirecipient audience signatures, AS communication confidentiality, and profile-combination obligations.

Limitations:

- This is a standards-level behavioral abstraction, not an implementation model.
- Concrete CBOR bytes, CWT/JWT/COSE/JOSE cryptographic validation, CoAP retransmission behavior, exact IANA registry mechanics, and profile-specific transports are abstracted into finite predicates.
- The SAL comments cite RFC 9200 section numbers and source line ranges from the attached RFC text.
