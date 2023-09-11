# Wssim
A simple lib for ws final slay simulation. Codes are in development and there's no documentation currently. if you want to try this project, refering "./include/testcase.hpp" might help you.
# Quick Start
1. Add a new test case function in ./include/testcase.hpp.
2. Update main.cc to call the new funciton. (`wssim::basic_bench` might help)
3. Build the code and run it.
``` shell
$ mkdir build && cd build
$ cmake ..
$ make
$ ./wssim_app
```
4. If you want to plot the result, please use `wssim::basic_bench_json`. This function will output results in json format, and a python script is provided to load this json file and plot the result. (Make sure you have installed matplotlib and numpy)
``` shell
$ pip install matplotlib numpy
$ python draw.py #in build dir
```

# Third party library
- [nlohmann/json](https://github.com/nlohmann/json)
- [bshoshany/thread-pool](https://github.com/bshoshany/thread-pool)