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
    bool is_space(wchar_t wc)
    {
        return std::iswspace(static_cast<wint_t>(wc));
    }

    auto timestamp_now(const char * format) -> decltype(std::put_time(std::declval<const std::tm *>(), std::declval<const char *>()))
    {
        const std::time_t now_time_t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        return std::put_time(std::localtime(&now_time_t), format);
    }
    std::string timestamp_now_str(const char * format)
    {
        return static_cast<std::stringstream&&>(std::stringstream() << timestamp_now(format)).str();
    }
}
