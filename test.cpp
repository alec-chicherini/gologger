//TESTED WITH MSVC 1928
//            GCC  90300


#include "gologger.h"
#ifdef _MSC_VER
#include <thread>
#elif __GNUC__
#include <future>

#endif


//TEST1 - general tests of all functionality.
//TEST2 - mulithreading test
#define TEST2
#define TEST3

int main() {
#ifdef _MSC_VER 
    std::cout << "Test for MSVC " << _MSC_VER << std::endl;
#elif __GNUC__
    std::cout << "Test for GCC " << (__GNUC__*10000+ __GNUC_MINOR__ *100 + __GNUC_PATCHLEVEL__) << std::endl;
#endif

    std::string name("output.csv"),
                sep(",");
    gologger log(sep, name);



#ifdef TEST1
    int ix = 4;
    //float fx = 5.5f;
    std::string str{ "lvalue string" };
    LOG(ID, ix, 123);
    LOG(ID, &ix);
    LOG(ID, "rvalue string", '+', ix);
    LOG(ID, LOCAL_TIME, FUNC);
    for (int i = 0; i < 10; i++) {
        LOG(ID, APP_TIME, LOCAL_TIME, FUNC, ix, str, "rvalue string", bool(1));
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    auto lambda = []() {return "from lambda string"; };
    LOG(ID, lambda());
#endif


#ifdef TEST2
    auto lambda_log = [](std::string&& str) { 
        for (int i = 0; i < 10; i++) {
        LOG(ID, APP_TIME,LOCAL_TIME, FUNC,str, std::this_thread::get_id());
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    } };

#ifdef _MSC_VER
    std::thread tr1(lambda_log, "lambda 1 msg");
    std::thread tr2(lambda_log, "lambda 2 msg");

 
    tr1.join();
    tr2.join();

#elif __GNUC__
    auto a1 = std::async(std::launch::async,lambda_log, "lambda 1 msg");
    auto a2 = std::async(std::launch::async, lambda_log, "lambda 2 msg");

    a1.wait();
    a2.wait();
#endif

#endif//TEST2
    
#ifdef TEST3


    auto vec = log.copy_log();

    for (auto& s : vec)std::cout << s << std::endl;

    log.save_log();

#endif
    return 0;
}