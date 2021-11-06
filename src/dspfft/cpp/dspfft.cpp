#include "../include/dspfft.hpp"

#include <prior/include/numbers.hpp>

#include <stdexcept>
#include <algorithm>
#include <numeric>
#include <functional>

DSPFFT_NAMESPACE_BEGIN

// calculate log2(x)
template <typename T, typename = typename ::std::enable_if<::std::is_unsigned<T>::value>::type>
PRIOR_NODISCARD PRIOR_CXX14_CONSTEXPR PRIOR_FORCED_INLINE
T
get_log_2_of_base_2(T x)
{
    T cnt = static_cast<T>(0);
    while (x != static_cast<T>(1))
    {
        ++cnt; x >>= 1;
    }
    return cnt;
}

template <typename T, typename = typename ::std::enable_if<::std::is_unsigned<T>::value>::type>
PRIOR_NODISCARD PRIOR_CXX14_CONSTEXPR PRIOR_FORCED_INLINE
T
reverse_bit(T x)
{
    static_assert(sizeof(T) <= 8, "Integer over 8 bytes has not been supported.");
    static_assert(sizeof(T) == 8 || sizeof(T) == 4 || sizeof(T) == 2 || sizeof(T) == 1, "The size of integer must be power of 2.");

                                       x = static_cast<T>(((x & static_cast<T>(0x5555555555555555ULL)) << 1 )
                                                        | ((x & static_cast<T>(0xAAAAAAAAAAAAAAAAULL)) >> 1 ));
                                       x = static_cast<T>(((x & static_cast<T>(0x3333333333333333ULL)) << 2 )
                                                        | ((x & static_cast<T>(0xCCCCCCCCCCCCCCCCULL)) >> 2 ));
    PRIOR_CONSTEXPR_IF(sizeof(T) >= 2) x = static_cast<T>(((x & static_cast<T>(0x0F0F0F0F0F0F0F0FULL)) << 4 )
                                                        | ((x & static_cast<T>(0xF0F0F0F0F0F0F0F0ULL)) >> 4 ));
    PRIOR_CONSTEXPR_IF(sizeof(T) >= 4) x = static_cast<T>(((x & static_cast<T>(0x00FF00FF00FF00FFULL)) << 8 )
                                                        | ((x & static_cast<T>(0xFF00FF00FF00FF00ULL)) >> 8 ));
    PRIOR_CONSTEXPR_IF(sizeof(T) >= 8) x = static_cast<T>(((x & static_cast<T>(0x0000FFFF0000FFFFULL)) << 16)
                                                        | ((x & 0xFFFF0000FFFF0000ULL) >> 16));
    constexpr int offset = sizeof(T) == 8 ? 32 : sizeof(T) == 4 ? 16 : sizeof(T) == 2 ? 8 : 4;
    return static_cast<T>((x >> offset) | (x << offset));
}

// Generate w_N for DFT
template <typename floating_type, typename = typename ::std::enable_if<::std::is_floating_point<floating_type>::value>::type>
PRIOR_NODISCARD PRIOR_FORCED_INLINE
::std::vector<::std::complex<floating_type>>
generate_w_n(typename ::std::vector<::std::complex<floating_type>>::size_type n)
{
    using complex_type = ::std::complex<floating_type>;
    ::std::vector<complex_type> w_n(n);
    decltype(n) i = 0;
    ::std::generate(w_n.begin(), w_n.end(),
                    [n, i]() mutable
                    {
                        constexpr auto e = prior::numbers::e_t<floating_type>::value;
                        constexpr auto pi = prior::numbers::pi_t<floating_type>::value;
                        return ::std::pow(complex_type(e, 0), complex_type(0, static_cast<floating_type>(-2.0L * pi * (i++) / n)));
                    });
    return w_n;
}

// FFT by frequency
template <typename floating_type, typename>
PRIOR_NODISCARD
::std::vector<::std::complex<floating_type>>
base_2_fft(const ::std::vector<::std::complex<floating_type>>& x)
{
    using size_type = decltype(x.size());
    using complex_type = ::std::complex<floating_type>;

    if (x.size() == 0) return {};
    if ((x.size() & (x.size() - 1)) != 0)   // not pow of 2
    {
        throw ::std::invalid_argument{"The length of signal is not pow of 2."};
    }

    auto w_n = generate_w_n<floating_type>(x.size());

    ::std::vector<complex_type> input(x.size());
    ::std::copy(x.begin(), x.end(), input.begin());

    ::std::vector<complex_type> result(x.size(), static_cast<complex_type>(0));
    auto stage_inc = static_cast<size_type>(1);
    auto stage_dec = x.size();
    for (; stage_dec != 1; stage_dec >>= 1, stage_inc <<= 1)
    {
        // stage_inc: group_num; stage_dec: per group
        auto half_of_group = stage_dec / 2;
        for (size_type group = 0; group < stage_inc; ++group)
        {
            auto offset = group * stage_dec;
            for (size_type idx = offset; idx < offset + half_of_group; ++idx)
            {
                result[idx] = input[idx] + input[idx + half_of_group];
                result[idx + half_of_group] = (input[idx] - input[idx + half_of_group]) * w_n[(idx - offset) * stage_inc];
            }
        }
        ::std::copy(result.begin(), result.end(), input.begin());
    }
    for (size_type i = 0; i < x.size(); ++i)
    {
        result[i] = input[reverse_bit(i) >> ((sizeof(i) * 8) - (get_log_2_of_base_2(x.size()) - 0))];
    }

    return result;
}

// Calculate DFT directly
template <typename floating_type, typename>
PRIOR_NODISCARD
::std::vector<::std::complex<floating_type>>
dft(const ::std::vector<::std::complex<floating_type>>& x)
{
    using size_type = decltype(x.size());
    using complex_type = ::std::complex<floating_type>;

    if (x.size() == 0) return {};

    auto w_n = generate_w_n<floating_type>(x.size());
    ::std::vector<complex_type> result(x.size());
    for (size_type k = 0; k < x.size(); ++k)
    {
        result[k] = ::std::inner_product(x.begin(), x.end(), w_n.begin(), complex_type{0}, ::std::plus<complex_type>{},
                             [k](complex_type x_n, complex_type w_n) { return x_n * static_cast<complex_type>(::std::pow(w_n, k)); });
    }

    return result;
}

#define DSPFFT_DECLARE_SPECIALIZATION(type, func) \
template \
::std::vector<::std::complex<type>> \
func<type>(const ::std::vector<::std::complex<type>>& x)

DSPFFT_DECLARE_SPECIALIZATION(float, base_2_fft);
DSPFFT_DECLARE_SPECIALIZATION(double, base_2_fft);
DSPFFT_DECLARE_SPECIALIZATION(long double, base_2_fft);

DSPFFT_DECLARE_SPECIALIZATION(float, dft);
DSPFFT_DECLARE_SPECIALIZATION(double, dft);
DSPFFT_DECLARE_SPECIALIZATION(long double, dft);

#undef DSPFFT_DECLARE_SPECIALIZATION

DSPFFT_NAMESPACE_END
