#include <iostream>
#include <dspfft.hpp>

int main()
{
    ::std::vector<::std::complex<double>> v { 1, 2, 3, 4, 5, 6, 7, 8 };
    auto r1 = dspfft::base_2_fft(v);
    auto r2 = dspfft::dft(v);
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
    return 0;
}
