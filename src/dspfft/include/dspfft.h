#ifndef DSPFFT_DSPFFT_H__
#define DSPFFT_DSPFFT_H__

#include <prior/include/prior.h>

#ifdef __cplusplus
#   include <cstddef>
#else // !defined(__cplusplus)
#   include <stddef.h>
#endif // #ifdef __cplusplus

DSPFFT_NAMESPACE_BEGIN

typedef struct
{
    float real;
    float imag;
} complexf;

typedef struct
{
    double real;
    double imag;
} complexl;

typedef struct
{
    long double real;
    long double imag;
} complexll;

// The return value of functins below is malloced and should be freed by the caller.

PRIOR_EXTERN_C_BEGIN

PRIOR_NODISCARD
complexf *
base_2_fftf(complexf *x, PRIOR_STD size_t len);

PRIOR_NODISCARD
complexl *
base_2_fftl(complexl *x, PRIOR_STD size_t len);

PRIOR_NODISCARD
complexll *
base_2_fftll(complexll *x, PRIOR_STD size_t len);

PRIOR_NODISCARD
complexf *
dftf(complexf *x, PRIOR_STD size_t len);

PRIOR_NODISCARD
complexl *
dftl(complexl *x, PRIOR_STD size_t len);

PRIOR_NODISCARD
complexll *
dftll(complexll *x, PRIOR_STD size_t len);

PRIOR_EXTERN_C_END

DSPFFT_NAMESPACE_END

#endif // #ifndef DSPFFT_DSPFFT_H__
