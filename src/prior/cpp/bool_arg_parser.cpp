#include "../include/bool_arg_parser.hpp"

#include <vector>
#include <string>
#include <unordered_set>
#include <stdexcept>

DSPFFT_NAMESPACE_BEGIN

::std::vector<char>
parse_bool_arg(::std::vector<char*> arg_pats, int argc, char* argv[])
{
    ::std::unordered_set<::std::string> args_hash;
    for (int i = 1; i < argc; ++i)
    {
        if (argv[i] == nullptr) throw ::std::invalid_argument("Internal error.");
        if (argv[i][0] != '-' || argv[i][1] != '-' || argv[i][2] == '\0') throw ::std::invalid_argument("Unknown options.");
        args_hash.emplace(argv[i] + 2);
    }
    ::std::vector<char> result;
    result.reserve(arg_pats.size());
    for (auto arg_pat : arg_pats)
    {
        auto itr = args_hash.find(::std::string(arg_pat));
        result.emplace_back(itr == args_hash.end() ? static_cast<char>(0) : static_cast<char>(1));
    }
    return result;
}

DSPFFT_NAMESPACE_END
