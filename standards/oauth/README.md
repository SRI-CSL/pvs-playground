# RFC 6749 OAuth 2.0 SAL Model Check

Model: `oauth2_rfc6749.sal`

SAL used:

```sh
sal-wfc oauth2_rfc6749.sal
sal-smc oauth2_rfc6749.sal
```

Results:

- `sal-wfc`: `Ok.`
- `sal-smc`: all 38 named `req_*` assertions are valid.

The model is a finite abstraction of RFC 6749:

- two client identities for client/code/refresh-token binding;
- confidential and public client classes, with web, user-agent, and native profiles;
- authorization-code, implicit, password, client-credentials, refresh-token, and extension grant flows;
- bounded scope lattice `[0..3]`, where lower/equal means no broader scope;
- endpoint behavior for authorization, token, redirection, and protected-resource access;
- abstract predicates for TLS, token entropy, JSON/cache headers, redirect validation, CSRF, sanitization, brute-force protection, and token-type understanding.

Theorems verified by `sal-smc`:

- `req_s1_2_access_token_precedes_resource`
- `req_s1_3_token_source_is_defined_grant`
- `req_s1_5_refresh_not_sent_to_resource_server`
- `req_s2_2_client_id_not_authentication`
- `req_s2_3_single_client_auth_method`
- `req_s2_3_1_password_auth_uses_tls`
- `req_s3_1_authorization_endpoint_tls_get`
- `req_s3_1_1_supported_response_types`
- `req_s3_1_2_invalid_redirect_not_followed`
- `req_s3_2_token_endpoint_tls_post`
- `req_s3_2_1_code_bound_to_requesting_client`
- `req_s3_3_scope_change_reported`
- `req_s4_1_authorization_code_single_use`
- `req_s4_1_expired_code_not_exchanged`
- `req_s4_1_redirect_uri_checked_on_code_exchange`
- `req_s4_2_implicit_no_refresh_token`
- `req_s4_2_implicit_token_in_fragment`
- `req_s4_3_password_credentials_discarded`
- `req_s4_3_password_grant_bruteforce_protected`
- `req_s4_4_client_credentials_confidential_only`
- `req_s4_4_client_credentials_authenticated`
- `req_s4_5_extension_grant_marked_as_extension`
- `req_s5_1_success_token_response_cache_headers`
- `req_s5_2_token_error_has_error_code`
- `req_s6_refresh_bound_to_client`
- `req_s6_refresh_scope_not_broadened`
- `req_s6_rotated_refresh_scope_identical`
- `req_s7_resource_requires_valid_token_scope_type`
- `req_s10_1_no_public_app_client_credentials`
- `req_s10_3_access_tokens_tls_and_unguessable`
- `req_s10_4_refresh_tokens_bound_and_unguessable`
- `req_s10_6_redirect_manipulation_prevented`
- `req_s10_8_no_cleartext_sensitive_credentials`
- `req_s10_9_endpoint_authenticity_tls`
- `req_s10_10_generated_credentials_unguessable`
- `req_s10_12_as_csrf_for_authorization`
- `req_s10_14_sanitize_state_and_redirect`
- `req_s10_15_open_redirector_blocked`

Limitations:

- This is a standards-level behavioral abstraction, not an implementation model.
- RFC syntax registries, IANA procedures, exact JSON/ABNF languages, HTTP transport mechanics, and cryptographic algorithms are represented by abstract state predicates rather than expanded into automata.
- RFC 6749 is marked by the IETF Datatracker as updated by later RFCs. This model targets RFC 6749 itself.
