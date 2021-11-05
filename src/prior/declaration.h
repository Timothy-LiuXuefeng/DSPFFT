#ifndef PRIOR_DECLRATION_H__
#define PRIOR_DECLRATION_H__

// C compatibility

#ifdef __cplusplus

#   define PRIOR_EXTERN_C extern "C"
#   define PRIOR_EXTERN_C_BEGIN extern "C" {
#   define PRIOR_EXTERN_C_END }

#   define PRIOR_STD ::std::

#else // !defined(__cplusplus)

#   define PRIOR_EXTERN_C
#   define PRIOR_EXTERN_C_BEGIN
#   define PRIOR_EXTERN_C_END

#   define PRIOR_STD

#endif // #ifdef __cplusplus

#endif // #ifndef PRIOR_DECLRATION_H__
