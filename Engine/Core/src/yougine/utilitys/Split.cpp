#pragma once
#include <vector>
#include <string>

namespace utility
{
    struct Split
    {
    public:
        static std::vector<std::string> SplitStr(const std::string s, char delim)
        {
            std::vector<std::string> elems;
            std::string s_chars;

            for (char c : s)
            {
                if (c == delim)
                {
                    if (!s_chars.empty())
                    {
                        elems.push_back(s_chars);
                    }
                    s_chars.clear();
                }
                else
                {
                    s_chars += c;
                }
            }

            if (!s_chars.empty())
            {
                elems.push_back(s_chars);
            }

            return elems;
        }
    };
}
