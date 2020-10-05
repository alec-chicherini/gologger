//helper class logger

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
#define ID logger::getId()
#define APP_TIME logger::getAppTime()
#define LOCAL_TIME logger::getLocalTime()
#define PRINT_LOG logger::printLog()
#define LOG(...) logger::log(__VA_ARGS__)

using namespace std;

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


class logger
{
    string output;
    static string separator;
    static int id;
    static vector<string> vecLog;
    static chrono::steady_clock::time_point start;
public:
    logger(string&& sep, string&& out) {
        separator = sep;
        output = out;
    };

    template<typename ...Ts>
    static void log(Ts...args) {
        ++id;

        stringstream res;

        auto t = std::make_tuple(args...);


        apply([&](auto&&... args) {

            ((res << args << logger::separator),...);

            //((cout<<args<<","),...);
            }, t);
        //cout<<endl;
        auto r = res.str();
        r.pop_back();
        vecLog.push_back(std::move(r));
    };



    static string getLocalTime() {

        time_t t = time(nullptr);
        std::tm tm{};
        localtime_s(&tm,&t);

        return
            to_string(tm.tm_hour) +
            ":" +
            to_string(tm.tm_min) +
            ":" +
            to_string(tm.tm_sec) +
            " " +
            to_string(tm.tm_mday) +
            "." +
            to_string(tm.tm_mon) +
            "." +
            to_string(tm.tm_year % 100);
          
    };

    static string getAppTime() {
        auto end = chrono::steady_clock::now();
        chrono::duration<double> d = end - start;

        return string(to_string(d.count()) + "s");
    };

    static string getId() {
        return to_string(id);
    };

    static void printLog() {
        for (auto& s : vecLog)
            cout << s << endl;
    };

};

int logger::id = 1;
vector<string> logger::vecLog{};
chrono::steady_clock::time_point logger::start = chrono::steady_clock::now();
string logger::separator = {};
int main() {

    logger log(",", "output.csv");
    int ix = 4;
    float fx = 5.5f;
    string str{ "lvalue string" };
    LOG(ID, ix, 123);
    LOG(ID, "rvalue string", '+', ix, fx);
    LOG(ID, LOCAL_TIME, FUNC);
    for (int i = 0; i < 100; i++) {
        LOG(ID, APP_TIME, LOCAL_TIME, FUNC, ix, fx, str, "rvalue", bool(1));
        this_thread::sleep_for(1ms);
    }
    PRINT_LOG;
    return 0;
}