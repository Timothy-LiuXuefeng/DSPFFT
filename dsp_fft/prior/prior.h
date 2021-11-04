#ifndef PRIOR_PRIOR_H__
#define PRIOR_PRIOR_H__

#include "compiler.h"
#include "namespace.h"

// C compatibility

#ifdef __cplusplus

#   define PRIOR_EXTERN_C extern "C"
#   define PRIOR_EXTERN_C_BEGIN extern "C" {
#   define PRIOR_EXTERN_C_END }

#else // !defined(__cplusplus)

#   define PRIOR_EXTERN_C
#   define PRIOR_EXTERN_C_BEGIN
#   define PRIOR_EXTERN_C_END

#endif // #ifdef __cplusplus

#endif // #ifndef PRIOR_PRIOR_H__
