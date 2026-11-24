;;; Load before pvs2c-theory. The application owns the observation streams.
(in-package :pvs)

(def-c-attach-primitive "crypto_random" "entropy_lookup" "uint16"
  '(|stream| |index|) '(|uint64| |uint32|)
  "{
    extern uint16_t crypto_entropy_lookup(uint64_t, uint32_t);
    return crypto_entropy_lookup(stream, index);
  }")

(def-c-attach-primitive "crypto_random" "prng_lookup" "uint16"
  '(|stream| |index|) '(|uint64| |uint32|)
  "{
    extern uint16_t crypto_prng_lookup(uint64_t, uint32_t);
    return crypto_prng_lookup(stream, index);
  }")
