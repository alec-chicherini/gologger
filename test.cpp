#include "gologger.h"
#include <thread>

int main() {

    gologger log(",", "output.csv");
    int ix = 4;
    float fx = 5.5f;
    std::string str{ "lvalue string" };
    LOG(ID, ix, 123);
    LOG(ID, "rvalue string", '+', ix, fx);
    LOG(ID, LOCAL_TIME, FUNC);
    for (int i = 0; i < 10; i++) {
        LOG(ID, APP_TIME, LOCAL_TIME, FUNC, ix, fx, str, "rvalue", bool(1));
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
   
    auto vec = log.copy_log();

    for (auto& s : vec)std::cout << s << std::endl;
    return 0;
}