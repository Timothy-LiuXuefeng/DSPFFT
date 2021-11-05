#ifndef DSPFFT_HPP__
#define DSPFFT_HPP__

#include <prior/prior.h>
#include <prior/numbers.hpp>

#include <type_traits>
#include <vector>
#include <complex>

DSPFFT_NAMESPACE_BEGIN

template <typename floating_type, typename = typename ::std::enable_if<::std::is_floating_point<floating_type>::value>::type>
PRIOR_NODISCARD
::std::vector<::std::complex<floating_type>>
base_2_fft(const ::std::vector<::std::complex<floating_type>>& x);

template <typename floating_type, typename = typename ::std::enable_if<::std::is_floating_point<floating_type>::value>::type>
PRIOR_NODISCARD
::std::vector<::std::complex<floating_type>>
dft(const ::std::vector<::std::complex<floating_type>>& x);

#define DSPFFT_DECLARE_EXTERN_SPECIALIZATION(type, func) \
extern template \
PRIOR_NODISCARD \
::std::vector<::std::complex<type>> \
func<type>(const ::std::vector<::std::complex<type>>& x)

DSPFFT_DECLARE_EXTERN_SPECIALIZATION(float, base_2_fft);
DSPFFT_DECLARE_EXTERN_SPECIALIZATION(double, base_2_fft);
DSPFFT_DECLARE_EXTERN_SPECIALIZATION(long double, base_2_fft);

DSPFFT_DECLARE_EXTERN_SPECIALIZATION(float, dft);
DSPFFT_DECLARE_EXTERN_SPECIALIZATION(double, dft);
DSPFFT_DECLARE_EXTERN_SPECIALIZATION(long double, dft);

#undef DSPFFT_DECLARE_EXTERN_SPECIALIZATION_OF_BASE_2_FFT

DSPFFT_NAMESPACE_END

#endif // #ifndef DSPFFT_HPP__
