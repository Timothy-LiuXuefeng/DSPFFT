#include <iostream>
#include <fstream>
#include <dspfft.hpp>
#include <prior/include/bool_arg_parser.hpp>
#include <prior/include/numbers.hpp>
#include <chrono>
#include <sstream>
#include <algorithm>
#include <cmath>
#include "format_complex.hpp"

PRIOR_NODISCARD PRIOR_FORCED_INLINE static
typename ::std::chrono::milliseconds::rep
get_milliseconds()
{
    return ::std::chrono::duration_cast<::std::chrono::milliseconds>(::std::chrono::system_clock::now().time_since_epoch()).count();
}

template <typename floating_type, typename = typename ::std::enable_if<::std::is_floating_point<floating_type>::value>::type>
PRIOR_NODISCARD PRIOR_FORCED_INLINE static
::std::string
generate_matlab_code(::std::vector<::std::complex<floating_type>> r)
{
    ::std::ostringstream sout;
    sout << "% MATLAB Code:\n";
    sout << "X = [";
    for (auto itr = r.begin(); ; )
    {
        sout << format_complex(*itr);
        if (++itr == r.end()) break;
        else sout << ", ";
    }
    sout << "];\n";
    return sout.str();
}

template <typename T, typename = typename ::std::enable_if<::std::is_unsigned<T>::value>::type>
PRIOR_NODISCARD PRIOR_CXX14_CONSTEXPR PRIOR_FORCED_INLINE static
T
ceil_to_pow_of_2(T x)
{
    static_assert(sizeof(T) <= 8, "Integer over 8 bytes has not been supported.");
    static_assert(sizeof(T) == 8 || sizeof(T) == 4 || sizeof(T) == 2 || sizeof(T) == 1, "The size of integer must be power of 2.");
    if (x == 0) return 1;
    auto r = x - 1;
                                       r |= r >> 1;
                                       r |= r >> 2;
                                       r |= r >> 4;
    PRIOR_CONSTEXPR_IF(sizeof(T) >= 2) r |= r >> 8;
    PRIOR_CONSTEXPR_IF(sizeof(T) >= 4) r |= r >> 16;
    PRIOR_CONSTEXPR_IF(sizeof(T) >= 8) r |= r >> 32;
    return r + 1;
}

int main_impl(const int argc, const char* const argv[])
{
    PRIOR_DECLARE_UNUSED_VARIABLE(argc);
    PRIOR_DECLARE_UNUSED_VARIABLE(argv);

    ::std::vector<const char*> pats
    {
        "enable-time-comparing",
        "writing-matlab-code-to-file",
        "debug"
    };

    auto options = ::prior::parse_bool_arg(pats, argc, argv);

    using point_t = ::std::size_t;

    if (options[0])
    {
        ::std::vector<::std::complex<double>> v;
        constexpr point_t n_point = ((point_t)1 << 15);
        point_t i = 0;
        v.reserve(n_point);
        ::std::generate_n(back_inserter(v), n_point, [i]() mutable noexcept { return ::std::complex<double>((double)++i, 0); });

        auto fft_begin = ::get_milliseconds();
        auto r1 = dspfft::base_2_fft(v);
        auto fft_end = ::get_milliseconds();
        ::std::cout << "FFT time: " << (fft_end - fft_begin) << "ms" << '\n';

        auto dft_begin = ::get_milliseconds();
        auto r2 = ::dspfft::dft(v);
        auto dft_end = ::get_milliseconds();
        ::std::cout << "DFT time: " << (dft_end - dft_begin) << "ms" << '\n';
        ::std::cout.flush();

        PRIOR_DECLARE_UNUSED_VARIABLE(r1);
        PRIOR_DECLARE_UNUSED_VARIABLE(r2);
    }

    if (options[1])
    {

        ::std::cout << "Analyse signal:\nPreparing..." << ::std::endl;

        point_t sample_rate = ((point_t)1 << 8);
        point_t total_time_in_second = (point_t)4;
        point_t total_points = sample_rate * total_time_in_second;
        point_t points_after_padding = ceil_to_pow_of_2(total_points);

        ::std::cout << "Calculating FFT..." << ::std::endl;

        ::std::vector<::std::complex<double>> v(points_after_padding, ::std::complex<double>(0, 0));
        point_t i = 0;
        ::std::generate_n(v.begin(), total_points,
                          [i, sample_rate]() mutable
                          {
                              constexpr auto pi_v = ::prior::numbers::pi_t<double>::value;
                              double t = (double)i++ / sample_rate;
                              return 0.8 * ::std::sin(2.0 * pi_v * 103.0 * t)
                                   +       ::std::sin(2.0 * pi_v * 107.0 * t)
                                   + 0.1 * ::std::sin(2.0 * pi_v * 115.0 * t);
                          }
                         );

        if (options[2])
        {
            for (auto itr = v.begin(); itr != v.end(); ++itr)
                ::std::cout << ::format_complex(*itr) << '\n';
            ::std::cout.flush();
        }

        auto res = ::dspfft::base_2_fft(v);

        ::std::cout << "Generating MATLAB Code..." << ::std::endl;

        ::std::ofstream fout("result.m", ::std::ios::out);
        fout << "% MATLAB Code:\nX = [";
        for (auto itr = res.begin(); ; )
        {
            fout << ::format_complex(*itr);
            if (++itr == res.end()) break;
            else fout << ", ";
        }
        fout << "];\n";
        fout.close();

        ::std::cout << "Finished. The MATLAB Code has been written into \'result.m\'." << ::std::endl;
    }
    return 0;
}

int main(int argc, char *argv[])
{
    return main_impl(argc, argv);
}
