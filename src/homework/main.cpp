#include <iostream>
#include <vector>
#include <complex>
#include <exception>
#include <stdexcept>
#include <numbers>
#include <algorithm>
#include <type_traits>
#include <cassert>
#include <iterator>
#include <cstdint>

constexpr double e_v = 2.718281828459045235360287471352662498L;
constexpr double pi_v = 3.141592653589793238462643383279502884L;

template <typename T, typename = typename ::std::enable_if<::std::is_unsigned<T>::value>::type>
[[nodiscard]] constexpr inline T get_log_2_of_base_2(T x)       // calculate log2(x)
{
    T cnt = static_cast<T>(0);
    while (x != static_cast<T>(1))
    {
        ++cnt; x >>= 1;
    }
    return cnt;
}

[[nodiscard]] constexpr inline ::std::uint64_t reverse_bit_64(::std::uint64_t x)
{
    x = static_cast<::std::uint64_t>(((x & 0x5555555555555555ULL) << 1) | ((x & 0xAAAAAAAAAAAAAAAAULL) >> 1));
    x = static_cast<::std::uint64_t>(((x & 0x3333333333333333ULL) << 2) | ((x & 0xCCCCCCCCCCCCCCCCULL) >> 2));
    x = static_cast<::std::uint64_t>(((x & 0x0F0F0F0F0F0F0F0FULL) << 4) | ((x & 0xF0F0F0F0F0F0F0F0ULL) >> 4));
    x = static_cast<::std::uint64_t>(((x & 0x00FF00FF00FF00FFULL) << 8) | ((x & 0xFF00FF00FF00FF00ULL) >> 8));
    x = static_cast<::std::uint64_t>(((x & 0x0000FFFF0000FFFFULL) << 16) | ((x & 0xFFFF0000FFFF0000ULL) >> 16));
    return static_cast<::std::uint64_t>((x >> 32) | (x << 32));
}

// FFT by frequency
template <typename floating_type, typename = typename ::std::enable_if<::std::is_floating_point<floating_type>::value>::type>
[[nodiscard]] ::std::vector<::std::complex<floating_type>> base_2_fft(const ::std::vector<::std::complex<floating_type>>& x)
{
    if (x.size() == 0) return {};
    if (x.size() & x.size() - 1 != 0)   // not pow of 2
    {
        throw ::std::invalid_argument{"The length of signal is not pow of 2."};
    }

    using size_type = decltype(x.size());
    using complex_type = ::std::complex<floating_type>;

    ::std::vector<complex_type> w_n(x.size());
    ::std::generate(w_n.begin(), w_n.end(), [n = 0, &x]() mutable { return ::std::pow(complex_type(e_v, 0), complex_type(0, -2.0L * pi_v * (n++) / x.size())); });

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
        result[i] = input[reverse_bit_64(static_cast<::uint64_t>(i)) >> (64 - (get_log_2_of_base_2(x.size()) - 0))];
    }

    return result;
}

int main()
{
    ::std::vector<::std::complex<double>> v { 1, 2, 3, 4, 5, 6, 7, 8 };
    auto r = base_2_fft(v);
    ::std::cout.precision(4);
    ::std::cout.flags(::std::ios::fixed);
    for (auto&& z : r)
    {
        ::std::cout << z.real() << "+j*" << z.imag() << ' ';
    }
    ::std::endl(::std::cout);
    return 0;
}
