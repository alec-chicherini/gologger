//#include "gologger.h"
//
//int main() {
//    std::string name("output.csv"),sep(",");
//
//    gologger log(sep, name);
//
//    int ix = 4;
//    float fx = 5.5f;
//    std::string str{ "lvalue string" };
//    LOG(ID, "one message");
//    LOG(ID, APP_TIME, LOCAL_TIME, FUNC, ix, fx, str, "literal string", std::string("rvalue string"), bool(1),1);
//    LOG(ID, APP_TIME, LOCAL_TIME, FUNC, ix, fx, str, "literal string", std::string("rvalue string"), bool(1),2);
//    LOG(ID, APP_TIME, LOCAL_TIME, FUNC, ix, fx, str, "literal string", std::string("rvalue string"), bool(1),3);
//    LOG(ID, APP_TIME, LOCAL_TIME, FUNC, ix, fx, str, "literal string", std::string("rvalue string"), bool(1),4);
//    LOG(1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8);
//
//    log.save_log();
//
//    auto vec(log.copy_log());
//
//    return 0;
//}