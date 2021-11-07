#ifndef PRIOR_RAW_BOOL_ARG_PARSER_H__
#define PRIOR_RAW_BOOL_ARG_PARSER_H__

#include "prior.h"

PRIOR_NAMESPACE_BEGIN

// The return value is malloced and should be free by the caller.
PRIOR_EXTERN_C
char *
raw_parse_bool_arg(const char *const *const arg_pats, const int pat_num, const int argc, const char *const argv[]);

PRIOR_NAMESPACE_END

#endif // #ifndef PRIOR_RAW_BOOL_ARG_PARSER_H__
