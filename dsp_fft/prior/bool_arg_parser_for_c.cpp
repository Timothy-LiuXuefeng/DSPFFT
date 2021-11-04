#include "bool_arg_parser_for_c.h"
#include "bool_arg_parser.hpp"

#include <cstdlib>
#include <cstring>

PRIOR_EXTERN_C
char *
parse_bool_arg_for_c(char **arg_pats, int pat_num, int argc, char *argv[])
{
    if (pat_num < 0) return NULL;
    try
    {
        ::std::vector<char*> arg_pat_vec(pat_num);
        for (int i = 0; i < pat_num; ++i)
        {
           arg_pat_vec[i] = arg_pats[i];
        }
        auto res_vec = dsp_fft::parse_bool_arg(arg_pat_vec, argc, argv);
        char *res = (char*)malloc(res_vec.size() * sizeof(char));
        ::std::memcpy(res, res_vec.data(), res_vec.size() * sizeof(char));
        return res;
    }
    catch(...)
    {
        return NULL;
    }
    return NULL;
}
