#ifndef PRIOR_COMPILER_H__
#define PRIOR_COMPILER_H__

#if defined(__GNUC__)
#   include "details/compiler_gcc.i"
#elif defined(__clang__)
#   include "details/compiler_clang.i"
#elif defined(_MSC_VER)
#   include "details/compiler_msvc.i"
#else
#   error This compiler is not supported. Please use GCC, Clang or MSVC.
#endif // defined(__GNUC__)

#endif // #ifndef PRIOR_COMPILER_H__
