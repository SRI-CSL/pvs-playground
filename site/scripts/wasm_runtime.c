/* Exact GMP implementation of Prelude exp2, without recursive C stack use.
 * The generated Prelude routine clears its input before the recursive branch
 * and uses one C frame per exponent. Keep the consuming PVS2C calling contract. */
#include "pvslib.h"
#include "exp2_c.h"

__typeof__(exp2__exp2) __wrap_exp2__exp2;

mpz_ptr_t __wrap_exp2__exp2(mpz_ptr_t exponent) {
    if (mpz_sgn(exponent) < 0 || !mpz_fits_ulong_p(exponent)) {
        pvs2cerror("PVS2C exp2 exponent exceeds the runtime's addressable size", 2);
    }
    mp_bitcnt_t bits = mpz_get_ui(exponent);
    release_mpz(exponent);
    mpz_ptr_t result = safe_malloc(sizeof(mpz_t));
    mpz_init_set_ui(result, 1);
    mpz_mul_2exp(result, result, bits);
    return result;
}
