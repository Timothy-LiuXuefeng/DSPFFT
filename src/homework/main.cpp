#include <iostream>
#include <sstream>
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

template <typename floating_type, typename = typename ::std::enable_if<::std::is_floating_point<floating_type>::value>::type>
PRIOR_NODISCARD PRIOR_FORCED_INLINE static
auto get_hanning(::std::size_t N) -> ::std::vector<::std::complex<double>>
{
    ::std::vector<::std::complex<floating_type>> res;
    res.reserve(N);
    ::std::size_t i = 0;
    ::std::generate_n(::std::back_inserter(res), N, [i, N]() mutable
                                                    {
                                                        constexpr auto pi = ::prior::numbers::pi_t<floating_type>::value;
                                                        return static_cast<floating_type>(0.5L * (1.0L - ::std::cos(2 * pi * i++ / (N - 1))));
                                                    });
    return res;
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

        auto get_fft_matlab_code = [](
                              point_t sample_rate,
                              point_t sample_points,
                              point_t total_points,
                              bool use_window
                          )
        {
            ::std::cout << "Analyse signal: "
                        << "sample_rate: " << sample_rate
                        << "; sample_points: " << sample_points
                        << "; total_points: " << total_points
                        << "; use_window: " << (use_window ? "true" : "false")
                        << "\nPreparing..." << ::std::endl;

            PRIOR_DECLARE_UNUSED_VARIABLE(use_window);

            ::std::cout << "Calculating FFT..." << ::std::endl;

            ::std::vector<::std::complex<double>> v(total_points, ::std::complex<double>(0, 0));
            point_t i = 0;

            if (use_window)
            {
                auto hanning = ::get_hanning<double>(total_points);
                ::std::generate_n(v.begin(), sample_points,
                            [i, sample_rate, &hanning]() mutable
                            {
                                constexpr auto pi_v = ::prior::numbers::pi_t<double>::value;
                                double t = (double)i / sample_rate;
                                return hanning[i++] * (0.8 * ::std::sin(2.0 * pi_v * 103.0 * t)
                                                     +       ::std::sin(2.0 * pi_v * 107.0 * t)
                                                     + 0.1 * ::std::sin(2.0 * pi_v * 115.0 * t));
                            }
                            );
            }
            else
            {
                ::std::generate_n(v.begin(), sample_points,
                            [i, sample_rate]() mutable
                            {
                                constexpr auto pi_v = ::prior::numbers::pi_t<double>::value;
                                double t = (double)i++ / sample_rate;
                                return 0.8 * ::std::sin(2.0 * pi_v * 103.0 * t)
                                     +       ::std::sin(2.0 * pi_v * 107.0 * t)
                                     + 0.1 * ::std::sin(2.0 * pi_v * 115.0 * t);
                            }
                            );
            }

            /*
            if (options[2])
            {
                for (auto itr = v.begin(); itr != v.end(); ++itr)
                    ::std::cout << ::format_complex(*itr) << '\n';
                ::std::cout.flush();
            }
            */

            auto res = ::dspfft::base_2_fft(v);

            ::std::cout << "Generating MATLAB Code..." << ::std::endl;

            ::std::ostringstream sout;
            sout << "[";
            for (auto itr = res.begin(); ; )
            {
                sout << ::format_complex(*itr);
                if (++itr == res.end()) break;
                else sout << ", ";
            }
            sout << "]";
            return sout.str();
        };

#ifdef TRANSFORM_TO_CRLF_NEWLINE
#   define NEWLINE "\r\n"
#else
#   define NEWLINE "\n"
#endif

        ::std::ofstream fout("result.m", ::std::ios::out);

        ::std::cout << "\nCompare sample rates:\n" << ::std::endl;

        {
            point_t sample_rates[] = { 100, 300, 800 };
            point_t sample_points = 800;
            point_t total_points = ceil_to_pow_of_2(sample_points);
            auto num = sizeof(sample_rates) / sizeof(point_t);
            for (int i = 0; i < (int)num; ++i)
            {
                fout << "X_1_" << i << " = " << get_fft_matlab_code(sample_rates[i], sample_points, total_points, false) << ";" NEWLINE;
                fout << "figure(1);" NEWLINE;
                fout << "t_1_" << i << " = linspace(0, 2 * pi * " << sample_rates[i] << " * (1 - 1 / length(X_1_" << i << ")), length(X_1_" << i << "));" NEWLINE;
                fout << "subplot(1, " << num << ", " << i + 1 << ");" NEWLINE;
                fout << "plot((0 : length(X_1_" << i << ") - 1) * " << sample_rates[i] << " / " << total_points << ", abs(X_1_" << i << "));" NEWLINE;
                fout << "title({\'sample rate: " << sample_rates[i]
                     << "\', \'sample points: " << sample_points
                     << "\', \'transfrom points: " << total_points << "\'});" NEWLINE;
            }
        }

        ::std::cout << "\nCompare sample points:\n" << ::std::endl;

        {
            point_t sample_rate = 300;
            point_t sample_points[] = { 300, 600, 1024 };
            point_t total_points = 1024;
            auto num = sizeof(sample_points) / sizeof(point_t);
            for (int i = 0; i < (int)num; ++i)
            {
                fout << "X_2_" << i << " = " << get_fft_matlab_code(sample_rate, sample_points[i], total_points, false) << ";" NEWLINE;
                fout << "figure(2);" NEWLINE;
                fout << "t_2_" << i << " = linspace(0, 2 * pi * " << sample_rate << " * (1 - 1 / length(X_2_" << i << ")), length(X_2_" << i << "));" NEWLINE;
                fout << "subplot(1, " << num << ", " << i + 1 << ");" NEWLINE;
                fout << "plot((0 : length(X_2_" << i << ") - 1) * " << sample_rate << " / " << total_points << ", abs(X_2_" << i << "));" NEWLINE;
                fout << "title({\'sample rate: " << sample_rate
                     << "\', \'sample points: " << sample_points[i]
                     << "\', \'transfrom points: " << total_points << "\'});" NEWLINE;
            }
        }

        ::std::cout << "\nCompare total points:\n" << ::std::endl;

        {
            point_t sample_rate = 300;
            point_t sample_points = 1024;
            point_t total_points[] = { 1024, 1024 * 2, 1024 * 8 };
            auto num = sizeof(total_points) / sizeof(point_t);
            for (int i = 0; i < (int)num; ++i)
            {
                fout << "X_3_" << i << " = " << get_fft_matlab_code(sample_rate, sample_points, total_points[i], false) << ";" NEWLINE;
                fout << "figure(3);" NEWLINE;
                fout << "t_3_" << i << " = linspace(0, 2 * pi * " << sample_rate << " * (1 - 1 / length(X_3_" << i << ")), length(X_3_" << i << "));" NEWLINE;
                fout << "subplot(1, " << num << ", " << i + 1 << ");" NEWLINE;
                fout << "plot((0 : length(X_3_" << i << ") - 1) * " << sample_rate << " / " << total_points[i] << ", abs(X_3_" << i << "));" NEWLINE;
                fout << "title({\'sample rate: " << sample_rate
                     << "\', \'sample points: " << sample_points
                     << "\', \'transfrom points: " << total_points[i] << "\'});" NEWLINE;
            }
        }

        ::std::cout << "\nComplare window function\n" << ::std::endl;

        {
            point_t sample_rate = 300;
            point_t sample_points = 300;
            point_t total_points = 1024;

            auto generate_code = [&](int row, int col, bool use_window)
            {
                fout << "X_4_" << col << " = " << get_fft_matlab_code(sample_rate, sample_points, total_points, use_window) << ";" NEWLINE;
                fout << "figure(4);" NEWLINE;
                fout << "t_4_" << col << " = linspace(0, 2 * pi * " << sample_rate << " * (1 - 1 / length(X_4_" << col << ")), length(X_4_" << col << "));" NEWLINE;
                fout << "subplot(2, 2, " << (row * 2 + col + 1) << ");" NEWLINE;
                fout << "plot((0 : length(X_4_" << col << ") - 1) * " << sample_rate << " / " << total_points << ", abs(X_4_" << col << "));" NEWLINE;
                fout << "title({\'sample rate: " << sample_rate
                     << "\', \'sample points: " << sample_points
                     << "\', \'transfrom points: " << total_points
                     << "\', \'use hanning window: " << (use_window ? "yes" : "no")
                     << "\'});" NEWLINE;
            };

            generate_code(0, 0, true);
            generate_code(0, 1, false);

            sample_points = 1024;
            generate_code(1, 0, true);
            generate_code(1, 1, false);
        }

        fout.close();

#undef NEWLINE

        ::std::cout << "Finished. The MATLAB Code has been written into \'result.m\'." << ::std::endl;
    }
    return 0;
}

int main(int argc, char *argv[])
{
    return main_impl(argc, argv);
}
