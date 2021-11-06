#ifndef DSPFFT_DSPFFT_DECL_H__
#define DSPFFT_DSPFFT_DECL_H__

#include <prior/include/prior.h>

#ifdef __cplusplus

#   define DSPFFT_NAMESPACE_BEGIN namespace dspfft {
#   define DSPFFT_NAMESPACE_END }

#else // !defined(__cplusplus)

#   define DSPFFT_NAMESPACE_BEGIN
#   define DSPFFT_NAMESPACE_END

#endif // #ifdef __cplusplus

#ifndef BUILDING_DSPFFT_LIB
REFERENCE_STATIC_LIB(dspfft)
#endif // #ifndef BUILDING_DSPFFT_LIB

#endif // #ifndef DSPFFT_DSPFFT_DECL_H__

