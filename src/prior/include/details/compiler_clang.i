#ifndef PRIOR_COMPILER_H__
#   error Please include <prior/compiler.h> instead.
#endif

// c++ version

#ifdef __cplusplus

#   if __cplusplus < 201103L
#       error Only C++11 or later versions of C++ is supported.
#   endif

#   if __cplusplus >= 201103L
#       define PRIOR_HAS_CXX11
#   endif

#   if __cplusplus >= 201402L
#       define PRIOR_HAS_CXX14
#   endif

#   if __cplusplus >= 201703L
#       define PRIOR_HAS_CXX17
#   endif

#endif // #ifdef __cplusplus

// attributes

#define PRIOR_FORCED_INLINE __attribute__((__always_inline__)) __inline__
#define PRIOR_NODISCARD __attribute__((__warn_unused_result__))
#define PRIOR_DECLARE_UNUSED_VARIABLE(x) ((void)(x))

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

// libraries

#define REFERENCE_STATIC_LIB(libname)
