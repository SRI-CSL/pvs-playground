// Regularized upper incomplete gamma used by the chi-square survival function.
#include <boost/math/special_functions/gamma.hpp>
#include <boost/math/special_functions/beta.hpp>
extern "C" double crypto_gamma_q(double a, double x) {
    return boost::math::gamma_q(a, x);
}

extern "C" double crypto_beta_i(double a, double b, double x) {
    return boost::math::ibeta(a, b, x);
}
