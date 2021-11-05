#ifndef PRIOR_BOOL_ARG_PARSER_FOR_C_H__
#define PRIOR_BOOL_ARG_PARSER_FOR_C_H__

#include "prior.h"

PRIOR_NAMESPACE_BEGIN

// The return value is malloced and should be free by the caller.
PRIOR_EXTERN_C
char *
raw_parse_bool_arg(char **arg_pats, int pat_num, int argc, char *argv[]);

PRIOR_NAMESPACE_END

#endif // #ifndef PRIOR_BOOL_ARG_PARSER_FOR_C_H__
