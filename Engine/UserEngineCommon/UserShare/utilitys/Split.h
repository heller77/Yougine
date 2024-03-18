#pragma once
#include <iostream>
#include <vector>
#include <string>

#include "../MacroDifHeader.h"

namespace utility
{
    class EXPORT Split
    {
    public:
        static std::vector<std::string> SplitStr(const std::string s, char delim);

    };
}
CEXTERN_EXPORT void Hello()
{
    std::cout << "hello" << std::endl;
}