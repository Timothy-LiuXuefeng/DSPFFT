#include "../include/dspfft.h"
#include "../include/dspfft.hpp"

#include <cstring>

DSPFFT_NAMESPACE_BEGIN

PRIOR_EXTERN_C_BEGIN

#define DSPFFT_GENERATE_FFT_FOR_C(postfix, type, func) \
PRIOR_NODISCARD \
complex##postfix * \
func##postfix(complex##postfix *x, ::std::size_t len) { \
    try { \
        ::std::vector<::std::complex<type>> v(len); \
        for (::std::size_t i = 0; i < len; ++i) { \
            v[i].real(x[i].real); v[i].imag(x[i].imag); \
        } \
        auto result_vec = func(v); \
        complex##postfix *result = (complex##postfix *)malloc(result_vec.size() * sizeof(complex##postfix)); \
        if (result == NULL) return NULL; \
        for (::std::size_t i = 0; i < result_vec.size(); ++i) { \
            result[i].real = result_vec[i].real(); result[i].imag = result_vec[i].imag(); \
        } \
        return result; \
    } \
    catch (...) { return NULL; } return NULL; \
}

DSPFFT_GENERATE_FFT_FOR_C(f, float, base_2_fft)
DSPFFT_GENERATE_FFT_FOR_C(l, double, base_2_fft)
DSPFFT_GENERATE_FFT_FOR_C(ll, long double, base_2_fft)

DSPFFT_GENERATE_FFT_FOR_C(f, float, dft)
DSPFFT_GENERATE_FFT_FOR_C(l, double, dft)
DSPFFT_GENERATE_FFT_FOR_C(ll, long double, dft)

#undef DSPFFT_GENERATE_FFT_FOR_C

PRIOR_EXTERN_C_END

DSPFFT_NAMESPACE_END
