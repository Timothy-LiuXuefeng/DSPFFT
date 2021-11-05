#ifndef PRIOR_BOOL_ARG_PARSER_HPP__
#define PRIOR_BOOL_ARG_PARSER_HPP__

#include "prior.h"

#include <vector>

PRIOR_NAMESPACE_BEGIN

PRIOR_NODISCARD
::std::vector<char>
parse_bool_arg(::std::vector<char*> arg_pats, int argc, char* argv[]);

PRIOR_NAMESPACE_END

#endif // #ifndef PRIOR_BOOL_ARG_PARSER_HPP__

