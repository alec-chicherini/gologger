#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <chrono>
#include <iomanip>
#include <ctime>
#include <concepts>
#include <thread>
#include <sstream>

#define FUNC __FUNCTION__
#define ID gologger::getId()
#define APP_TIME gologger::getAppTime()
#define LOCAL_TIME gologger::getLocalTime()
#define LOG(...) gologger::log(__VA_ARGS__)

class gologger
{
    std::string output;
    static std::string separator;
    static int id;
    static std::vector<std::string> vecLog;
    static std::chrono::steady_clock::time_point start;

    public:

        //constructor
        //sep - separator symbol like "," or "\" or " " ..
        gologger(std::string&& sep, std::string&& out);

        //LOG
        //make log entrance with variable number of arguments 
        template<typename ...Ts>
        static void log(Ts...args) {
            ++id;

            std::stringstream res;

            auto t = std::make_tuple(args...);


            apply([&](auto&&... args) {

                ((res << args << gologger::separator), ...);

                //((cout<<args<<","),...);
                }, t);
            //cout<<endl;
            auto r = res.str();
            r.pop_back();
            vecLog.push_back(std::move(r));
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


};

