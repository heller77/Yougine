#pragma once
#include <vector>
#include <string>

namespace utility
{
    struct Split
    {
    public:
        static std::vector<std::string> SplitStr(const std::string s, char delim);

    };
}
