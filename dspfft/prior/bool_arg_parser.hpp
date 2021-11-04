#ifndef BOOL_ARG_PARSER_HPP__
#define BOOL_ARG_PARSER_HPP__

#include "prior.h"

#include <vector>

DSP_FFT_NAMESPACE_BEGIN

PRIOR_NODISCARD
::std::vector<char>
parse_bool_arg(::std::vector<char*> arg_pats, int argc, char* argv[]);

DSP_FFT_NAMESPACE_END

#endif // #ifndef BOOL_ARG_PARSER_HPP__

