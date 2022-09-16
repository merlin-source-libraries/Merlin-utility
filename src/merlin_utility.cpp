#include <merlin_utility.hpp>

#include <cctype>
#include <chrono>
#include <sstream>

namespace merl
{
    bool is_space(char c)
    {
        return std::isspace(static_cast<unsigned char>(c));
    }
    std::string trim(std::string_view sv)
    {
        unsigned long long b_pos = 0;
        long long e_pos = sv.size()-1;

        while(b_pos < sv.size() && is_space(sv[b_pos]))
            ++b_pos;

        while(e_pos >= 0 && is_space(sv[e_pos]))
            --e_pos;

        return std::string(sv.substr(b_pos, e_pos-b_pos+1));
    }

    auto timestamp_now(const char * format) -> decltype(std::put_time(std::declval<const std::tm *>(), std::declval<const char *>()))
    {
        const std::time_t now_time_t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        return std::put_time(std::localtime(&now_time_t), format);
    }
    std::string timestamp_now_str(const char * format)
    {
        return dynamic_cast<std::stringstream&>(std::stringstream() << timestamp_now(format)).str();
    }
}