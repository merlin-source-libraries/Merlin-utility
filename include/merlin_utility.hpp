#ifndef MERLIN_UTILITY_HPP
#define MERLIN_UTILITY_HPP

#include <string>
#include <string_view>
#include <iomanip>
#include <chrono>

namespace merl
{
    bool is_space(char c);
    bool is_space(wchar_t wc);
    
    template <typename CharT>
    std::basic_string<CharT> trim(std::basic_string_view<CharT> sv)
    {
        unsigned long long b_pos = 0;
        long long e_pos = sv.size()-1;

        while(b_pos < sv.size() && is_space(sv[b_pos]))
            ++b_pos;

        while(e_pos >= 0 && is_space(sv[e_pos]))
            --e_pos;

        return std::basic_string<CharT>(sv.substr(b_pos, e_pos-b_pos+1));
    }

    template <typename CharT, template <typename...> class Container>
    Container<std::basic_string<CharT>> split(std::basic_string_view<CharT> sv, CharT delim)
    {
        Container<std::basic_string<CharT>> res;

        std::basic_string<CharT> word;
        for(CharT c : sv)
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

    template <typename Tref = std::chrono::milliseconds, typename F, typename ... Args>
    typename Tref::rep profile(F && f, Args && ... args)
    {
        static_assert(std::is_invocable<F, Args...>::value, "F type must be callable with the arguments types Args... such that f(args...) would be well-formed");

        auto start = std::chrono::steady_clock::now();
        f(std::forward<Args...>(args)...);
        auto end = std::chrono::steady_clock::now();

        return std::chrono::duration_cast<Tref>(end - start).count();
    }
}

#endif