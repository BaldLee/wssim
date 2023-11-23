# Wssim

A simple library for simulating Weiß Schwarz finishers. The code is still under development, and there is no documentation available at this time. If you want to try this project, please refer to `include/testcase.hpp` for guidance.

# Quick Start

1. Create a new test case function in `./include/testcase.hpp`.
2. Update `main.cc` to call the new function. (The `wssim::basic_bench` function may be helpful.)
3. Build the code and run it.

``` shell
$ mkdir build && cd build
$ cmake ..
$ make
$ ./wssim_app
```

4. If you want to plot the results, use the `wssim::basic_bench_json` function. This function will output the results in JSON format. A Python script is provided to load this JSON file and plot the results. (Make sure you have installed matplotlib and numpy.)

``` shell
$ pip install matplotlib numpy
$ python draw.py #in build dir
```

# Third party library
- [nlohmann/json](https://github.com/nlohmann/json)
- [bshoshany/thread-pool](https://github.com/bshoshany/thread-pool)
