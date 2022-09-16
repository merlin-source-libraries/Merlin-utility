#ifndef MERLIN_UTILITY_HPP
#define MERLIN_UTILITY_HPP

#include <string>
#include <string_view>
#include <iomanip>

namespace merl
{
    bool is_space(char c);
    std::string trim(std::string_view sv);

    template <template <typename...> class Container>
    Container<std::string> split(std::string_view sv, char delim)
    {
        Container<std::string> res;

        std::string word;
        for(char c : sv)
        {
            if(c == delim && !word.empty())
            {
                res.push_back(word);
                word.clear();
            }
            else
                word += c;
        }
        if(!word.empty())
            res.push_back(word);

        return res;
    }

    auto timestamp_now(const char * format) -> decltype(std::put_time(std::declval<const std::tm *>(), std::declval<const char *>()));
    std::string timestamp_now_str(const char * format);
}

#endif