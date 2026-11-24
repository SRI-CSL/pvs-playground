(in-package :pvs)

(def-c-attach-primitive "crypto_statistics" "fl" "uint64"
  '(|x|) '(|uint64|)
  "{ return crypto_fp((double)x); }")

(def-c-attach-primitive "crypto_statistics" "fp_add" "uint64"
  '(|x| |y|) '(|uint64| |uint64|)
  "{ return crypto_fp(crypto_double(x) + crypto_double(y)); }")

(def-c-attach-primitive "crypto_statistics" "fp_sub" "uint64"
  '(|x| |y|) '(|uint64| |uint64|)
  "{ return crypto_fp(crypto_double(x) - crypto_double(y)); }")

(def-c-attach-primitive "crypto_statistics" "fp_mul" "uint64"
  '(|x| |y|) '(|uint64| |uint64|)
  "{ return crypto_fp(crypto_double(x) * crypto_double(y)); }")

(def-c-attach-primitive "crypto_statistics" "fp_div" "uint64"
  '(|x| |y|) '(|uint64| |uint64|)
  "{ return crypto_fp(crypto_double(x) / crypto_double(y)); }")

(def-c-attach-primitive "crypto_statistics" "fp_lt" "bool"
  '(|x| |y|) '(|uint64| |uint64|)
  "{ return crypto_double(x) < crypto_double(y); }")

(def-c-attach-primitive "crypto_statistics" "fp_pow" "uint64"
  '(|x| |y|) '(|uint64| |uint64|)
  "{ return crypto_fp(pow(crypto_double(x),crypto_double(y))); }")

(def-c-attach-primitive "crypto_statistics" "gamma_q" "uint64"
  '(|x| |y|) '(|uint64| |uint64|)
  "{ return crypto_fp(crypto_gamma_q(crypto_double(x),crypto_double(y))); }")

(def-c-attach-primitive "crypto_statistics" "fp_abs" "uint64"
  '(|x|) '(|uint64|)
  "{ return crypto_fp(fabs(crypto_double(x))); }")

(def-c-attach-primitive "crypto_statistics" "fp_sqrt" "uint64"
  '(|x|) '(|uint64|)
  "{ return crypto_fp(sqrt(crypto_double(x))); }")

(def-c-attach-primitive "crypto_statistics" "fp_log" "uint64"
  '(|x|) '(|uint64|)
  "{ return crypto_fp(log(crypto_double(x))); }")

(def-c-attach-primitive "crypto_statistics" "fp_exp" "uint64"
  '(|x|) '(|uint64|)
  "{ return crypto_fp(exp(crypto_double(x))); }")

(def-c-attach-primitive "crypto_statistics" "fp_erfc" "uint64"
  '(|x|) '(|uint64|)
  "{ return crypto_fp(erfc(crypto_double(x))); }")

(def-c-attach-primitive "crypto_statistics" "fp_sin" "uint64"
  '(|x|) '(|uint64|)
  "{ return crypto_fp(sin(crypto_double(x))); }")

(def-c-attach-primitive "crypto_statistics" "fp_cos" "uint64"
  '(|x|) '(|uint64|)
  "{ return crypto_fp(cos(crypto_double(x))); }")

(def-c-attach-primitive "crypto_statistics" "fp_log1p" "uint64"
  '(|x|) '(|uint64|)
  "{ return crypto_fp(log1p(crypto_double(x))); }")

(def-c-attach-primitive "crypto_statistics" "fp_expm1" "uint64"
  '(|x|) '(|uint64|)
  "{ return crypto_fp(expm1(crypto_double(x))); }")

(def-c-attach-primitive "crypto_compression" "bzip2_length" "uint32"
  '(|x|) '(|crypto_compression__buffer|)
  "" "{
    extern uint32_t crypto_bzip_length(const uint8_t *, uint32_t);
    uint32_t result = crypto_bzip_length(x->seq->elems, x->length);
    release_crypto_compression__buffer(x);
    return result;
  }")

(def-c-attach-primitive "crypto_statistics" "beta_i" "uint64"
  '(|a| |b| |x|) '(|uint64| |uint64| |uint64|)
  "{ return crypto_fp(crypto_beta_i(crypto_double(a),crypto_double(b),crypto_double(x))); }")
