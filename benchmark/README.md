# ccbench_v2/benchmark
Benchmark of TPC-C and YCSB

## TPC-C-NP
Now, This provides TPC-C-NP benchmark.
- [wip] TPC-C - full mix

### Build
```
$ cd [to/ ccbench_v2]
$ mkdir build
$ cd build
$ cmake -DCMAKE_BUILD_TYPE=Release ..
$ make -j
```

### Run
- runtime options
  - `-thread_num` : Total number of worker threads.
    - default : `1`
  - `-clocks_per_us` : Use this info for measuring time.
    - default : `2100`
  - `-epoch_time` : Epoch interval [msec].
    - default : `40`
  - `-extime` : Execution time [sec].
    - default : `1`
  - `-num_wh` : The number of warehouses.
    - default : `1`
  - `-perc_payment` : The percentage of Payment transactions.
    - default : `50`
  - `-perc_order_status` : The percentage of Order_Status transactions.
    - default : `0`
  - `-perc_delivery` : The percentage of Delivery transactions.
    - default : `0`
  - `-perc_stock_level` : The percentage of Stock-Level transactions.
    - default : `0`
- example
```
$ ./benchmark/bench.exe -extime 5
```
- note : If you want to avoid contentions against global heap, you should use appropriate  memory allocator.
```
$ LD_PRELOAD=[path/to/some memory allocator] ./benchmark/bench.exe
```

## [wip] YCSB
