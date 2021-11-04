#ifndef BOOL_ARG_PARSER_FOR_C_H__
#define BOOL_ARG_PARSER_FOR_C_H__

#include "prior.h"

// The return value is malloced and should be free by the caller.
PRIOR_EXTERN_C
char *
parse_bool_arg_for_c(char **arg_pats, int pat_num, int argc, char *argv[]);

#endif // #ifndef BOOL_ARG_PARSER_FOR_C_H__
