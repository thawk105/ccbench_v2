/**
 * @file common.hh
 * @biref common information for benchmark
 */

#pragma once

#include <pthread.h>
#include <atomic>
#include <iostream>
#include <queue>

#include "cpu.h"
#include "int64byte.hh"
#include "tuple.h"

#include "gflags/gflags.h"
#include "glog/logging.h"

#ifdef GLOBAL_VALUE_DEFINE
#define GLOBAL
alignas(CACHE_LINE_SIZE) GLOBAL uint64_t_64byte GlobalEpoch(1);
#else // GLOBAL_VALUE_DEFINE
#define GLOBAL extern
alignas(CACHE_LINE_SIZE) GLOBAL uint64_t_64byte GlobalEpoch;
#endif // GLOBAL_VALUE_DEFINE

#ifdef GLOBAL_VALUE_DEFINE
DEFINE_uint64(thread_num, 1, "Total number of worker threads.");
DEFINE_uint64(clocks_per_us, 2100,
              "CPU_MHz. Use this info for measuring time.");
DEFINE_uint64(epoch_time, 40, "Epoch interval[msec].");
DEFINE_uint64(extime, 1, "Execution time[sec].");
#ifdef BENCH_TPCC
DEFINE_uint32(num_wh, 1, "The number of warehouses");
DEFINE_uint64(perc_payment, 50, "The percentage of Payment transactions"); // 43.1 for full
DEFINE_uint64(perc_order_status, 0, "The percentage of Order-Status transactions"); // 4.1 for full
DEFINE_uint64(perc_delivery, 0, "The percentage of Delivery transactions"); // 4.2 for full
DEFINE_uint64(perc_stock_level, 0, "The percentage of Stock-Level transactions"); // 4.1 for full
#endif
#else
DECLARE_uint64(thread_num);
DECLARE_uint64(clocks_per_us);
DECLARE_uint64(epoch_time);
DECLARE_uint64(extime);
#ifdef BENCH_TPCC
DECLARE_uint32(num_wh);
DECLARE_uint64(perc_payment);
DECLARE_uint64(perc_order_status);
DECLARE_uint64(perc_delivery);
DECLARE_uint64(perc_stock_level);
#endif
#endif
