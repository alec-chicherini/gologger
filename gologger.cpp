#include "gologger.h"
std::mutex gologger::log_mtx;
std::atomic<long long> gologger::id = 1;
std::vector<std::string> gologger::vecLog{};
std::chrono::steady_clock::time_point gologger::start = std::chrono::steady_clock::now();
std::string gologger::separator = {};

//using string stream instead operator+
/*
template<typename T>
concept to_string_convertible =
requires(T x){to_string(x);};

auto any_to_string=
[]<typename T>(T&& x)
requires to_string_convertible <T>
{return to_string(x);};
*/


gologger::gologger(std::string sep, std::string out) {
        separator = sep;
        output = out;
    };

    

     std::string gologger::getLocalTime() {

        time_t t = time(nullptr);
        std::tm tm{};
        localtime_s(&tm, &t);

        return
            std::to_string(tm.tm_hour) +
            ":" +
            std::to_string(tm.tm_min) +
            ":" +
            std::to_string(tm.tm_sec) +
            " " +
            std::to_string(tm.tm_mday) +
            "." +
            std::to_string(tm.tm_mon+1) +
            "." +
            std::to_string(tm.tm_year % 100);

    };

     std::string gologger::getAppTime() {
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> d = end - start;

        return std::string(std::to_string(d.count()) + "s");
    };

     std::string gologger::getId() {
        return std::to_string(id);
    };

    
     std::vector<std::string> gologger::copy_log() {
         return vecLog;
     };
    



