#include <iostream>
#include <dspfft.hpp>
#include <prior/include/bool_arg_parser.hpp>
#include "format_complex.hpp"

int main(int argc, char* argv[])
{
    PRIOR_DECLARE_UNUSED_VARIABLE(argc);
    PRIOR_DECLARE_UNUSED_VARIABLE(argv);

    // ::std::vector<char*>

    ::std::vector<::std::complex<double>> v;
    auto r1 = dspfft::base_2_fft(v);
    auto r2 = dspfft::dft(v);

    /*
    ::std::cout.precision(4);
    ::std::cout.flags(::std::ios::fixed);
    for (auto&& z : r1)
    {
        ::std::cout << z.real() << "+j*" << z.imag() << ' ';
    }
    ::std::endl(::std::cout);
    for (auto&& z : r2)
    {
        ::std::cout << z.real() << "+j*" << z.imag() << ' ';
    }
    ::std::endl(::std::cout);
    */

    ::std::cout << "% MATLAB Code:" << ::std::endl;
    ::std::cout << "X = [";
    for (auto itr = r1.begin(); ; )
    {
        ::std::cout << format_complex(*itr);
        if (++itr == r1.end()) break;
        else ::std::cout << ", ";
    }
    ::std::cout << "];" << ::std::endl;
    return 0;
}
