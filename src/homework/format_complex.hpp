#ifndef FORMAT_COMPLEX_HPP__
#define FORMAT_COMPLEX_HPP__

#include <string>
#include <sstream>
#include <complex>
#include <type_traits>
#include <cmath>
#include <prior/include/prior.h>

// format complex to MATLAB pattern
template <typename floating_type, typename = typename ::std::enable_if<::std::is_floating_point<floating_type>::value>::type>
PRIOR_NODISCARD
::std::string
format_complex(::std::complex<floating_type> z)
{
    if (::std::isnan(z.real()) || ::std::isnan(z.real()))
    {
        return "NaN + NaN * j";
    }
    ::std::ostringstream sout;
    if (::std::isinf(z.real()))
    {
        sout << (z.real() > 0 ? "Inf" : "-Inf");
    }
    else sout << z.real();
    sout.put(' ');

    if (::std::isinf(z.imag()))
    {
        sout << (z.real() > 0 ? "+ Inf" : "- Inf");
    }
    else if (z.imag() < 0) sout << "- " << -z.imag();
    else sout << "+ " << z.imag();
    sout << " * j";
    return sout.str();
}

#endif // #ifndef FORMAT_COMPLEX_HPP__
