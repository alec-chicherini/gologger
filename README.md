## gologger
Just go and make log :)

After make some tasks where i  was need to use different logs  i made this small logger for my toolbox. May be for someone it will be helpfull.

### Features

-Up to 64 different params in one LOG string.

-Support fundamental types in c++.

-Support std::strings.

-Support lvalues and rvalues.

### What to do

- Initialisation. Just add header file and make gologger object in main function(if u use console).
  
```cpp

#include "gologger.h"

int main() {
    std::string name("output.csv"),sep(",");
    //name - output file name
    //sep - string to separate different entry inside one string.(in example i`m using "," to oppen like .csv file.)
    gologger log(sep, name);
 ```
 
- Using. Make log entry with LOG macro with different params. In different threads. 
 ```cpp
    LOG(ID, "one message");
    LOG(ID, APP_TIME, LOCAL_TIME, FUNC, ix, fx, str, "literal string", std::string("rvalue string"), bool(1),1);
    LOG(ID, APP_TIME, LOCAL_TIME, FUNC, ix, fx, str, "literal string", std::string("rvalue string"), bool(1),2);
    LOG(ID, APP_TIME, LOCAL_TIME, FUNC, ix, fx, str, "literal string", std::string("rvalue string"), bool(1),3);
    LOG(ID, APP_TIME, LOCAL_TIME, FUNC, ix, fx, str, "literal string", std::string("rvalue string"), bool(1),4);
 ```
 - Macros. Some useful built-in macros.
```cpp
//Return function where log called.
#define FUNC 

//Get current - next id for log entrance. Every log entry is counting. Was it added  to LOG() or not.
#define ID 

//Get time from gologer initialisation to using this LOG macro.
#define APP_TIME 

//Get current system time.
#define LOCAL_TIME 
```
 
 - Save or copy. Save log to file or copy to another std::vector<std::string> to use it in client side.
 ```cpp
    log.save_log();

    auto vec(log.copy_log());
 ```
 - What else? Check test.cpp file for more examples.
