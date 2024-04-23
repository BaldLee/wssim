# Wssim

A simple library for simulating Weiß Schwarz finishers. This repo is still under development, and there is no documentation available at this time. If you want to try this project, please refer to `example/single_sim.cc` for guidance.

## Quick Start

1. Create a new test case function in `example/single_sim.cc`.
2. Update the main function to call the new function. (The `wssim::benchmark` function may be helpful.)
3. Build the code and run it. You will get a `out.json` file including the results.

``` shell
$ mkdir build && cd build
$ cmake ..
$ make -j
$ example/single_sim
```

4. If you want to plot the results, use the script `python/plot_output.py`. (Make sure you have installed matplotlib and numpy.)

``` shell
$ # pip install matplotlib numpy
$ python ../python/plot_output.py -f ./output.json -t "The title" #in build dir
```

## Third party library
- [nlohmann/json](https://github.com/nlohmann/json)
- [bshoshany/thread-pool](https://github.com/bshoshany/thread-pool)
