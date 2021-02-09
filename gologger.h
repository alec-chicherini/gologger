#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <chrono>
#include <sstream>
#include <atomic>
#include <mutex>
#include <fstream>
#include <ctime>


//Function where log called

#ifdef _MSC_VER
#define FUNC __FUNCSIG__
#elif __GNUC__
#define FUNC __PRETTY_FUNCTION__
#endif
//Get current - next id for log entrance
#define ID gologger::getId()

//Get time from gologer init to now
#define APP_TIME gologger::getAppTime()

//Get current system time
#define LOCAL_TIME gologger::getLocalTime()

//Make log entrance with variable number of arguments: basic tipes in lvalues and rvalues. And macros ID, APP_TIME, LOCAL_TIME, FUNC
#define LOG(...) gologger::log(__VA_ARGS__)

class gologger
{
    std::string output;
    static std::mutex log_mtx;
    static std::string separator;
    static std::atomic<long long> id;
    static std::vector<std::string> vecLog;
    static std::chrono::steady_clock::time_point start;

    public:

        //constructor
        //sep - separator symbol like "," or "\" or " " etc
        gologger(std::string sep, std::string out);

        //LOG
        //make log entrance with variable number of arguments 
        template<typename ...Ts>
        static void log(Ts...args) {
            id.fetch_add(1,std::memory_order_relaxed);

            std::stringstream res;

            auto t = std::make_tuple(args...);

            apply([&](auto&&... args) 
                {
                ((res << args << gologger::separator), ...);
                }, t);
          
            auto r = res.str();
            r.pop_back();
            log_mtx.lock();
            vecLog.push_back(std::move(r));
            log_mtx.unlock();

        };

       //LOCAL_TIME
       //return string with local time
       static std::string getLocalTime();

       //APP_TIME
       //return the time since log object initialised
       static std::string getAppTime();

       //ID
       //return string wit current ID entrance
       static std::string getId();

       //returning a log in std::vector<std::string>
       std::vector<std::string> copy_log();

       //Save log by output name.
       bool save_log();
};

