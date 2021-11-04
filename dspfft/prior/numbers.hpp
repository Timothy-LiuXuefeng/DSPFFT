#ifndef PRIOR_NUMBERS_HPP__
#define PRIOR_NUMBERS_HPP__

#include "prior.h"

#include <type_traits>

DSPFFT_NAMESPACE_BEGIN

template <typename floating_type, typename = typename ::std::enable_if<::std::is_floating_point<floating_type>::value>::type>
PRIOR_CONSTEXPR
floating_type e = static_cast<floating_type>(2.718281828459045235360287471352662498L);

template <typename floating_type, typename = typename ::std::enable_if<::std::is_floating_point<floating_type>::value>::type>
PRIOR_CONSTEXPR
floating_type pi = static_cast<floating_type>(3.141592653589793238462643383279502884L);

DSPFFT_NAMESPACE_END

#endif // #ifndef PRIOR_NUMBERS_HPP__
