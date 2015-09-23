# simple-timer
 Lightweight C++ thread-safe timer

#### Features
* C++11
* header-only
* thread-safe (Linux only)


#### Installation
As the library is header-only, just include it in your project:
```c++
#include "SimpleTimer.h"
```


#### Usage
Start a timer and give it a name
```c++
SimpleTimer::get().start("Timer #1");
```

Stop the timer when you're done, using the name you provided
```c++
SimpleTimer::get().stop("Timer #1");
```

Get the time in milliseconds, micro-seconds and seconds
```c++
SimpleTimer::get().getTime<ms>("Timer #1");
SimpleTimer::get().getTime<micro>("Timer #1");
SimpleTimer::get().getTime<sec>("Timer #1");
```
