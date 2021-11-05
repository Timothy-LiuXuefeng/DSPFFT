#ifndef PRIOR_COMPILER_H__
#   error Please include <prior/compiler.h> instead.
#endif

// version

#ifdef __cplusplus

#   if _MSVC_LANG < 201402L
#       error Only /std:c++14 or later options of C++ language version is supported on MSVC.
#   endif

#   define PRIOR_HAS_CXX11

#   if _MSVC_LANG >= 201402L
#       define PRIOR_HAS_CXX14
#   endif

#   if _MSVC_LANG >= 201703L
#       define PRIOR_HAS_CXX17
#   endif

#endif // #ifdef __cplusplus

// attributes

#define PRIOR_FORCED_INLINE __forceinline
#define PRIOR_NODISCARD _Check_return_

#ifdef __cplusplus

#   define PRIOR_CONSTEXPR constexpr

#   if defined(PRIOR_HAS_CXX14)
#       define PRIOR_CXX14_CONSTEXPR constexpr
#   else
#       define PRIOR_CXX14_CONSTEXPR
#   endif

#   if defined(PRIOR_HAS_CXX17)
#       define PRIOR_CONSTEXPR_IF if constexpr
#   else
#       define PRIOR_CONSTEXPR_IF if
#   endif

#endif // #ifdef __cplusplus
