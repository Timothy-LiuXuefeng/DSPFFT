#ifndef PRIOR_BOOL_ARG_PARSER_HPP__
#define PRIOR_BOOL_ARG_PARSER_HPP__

#include "prior.h"

#include <vector>

PRIOR_NAMESPACE_BEGIN

PRIOR_NODISCARD
::std::vector<char>
parse_bool_arg(::std::vector<const char*> arg_pats, const int argc, const char* const argv[]);

PRIOR_NAMESPACE_END

#endif // #ifndef PRIOR_BOOL_ARG_PARSER_HPP__

