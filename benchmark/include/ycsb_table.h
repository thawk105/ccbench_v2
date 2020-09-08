/**
 * @file ycsb_table.h
 * @biref common information for ycsb benchmark
 */

#pragma once

#include <pthread.h>
#include <atomic>
#include <iostream>
#include <queue>

#include "cpu.h"
#include "int64byte.hh"
#include "tuple.h"

// about index
#ifdef BENCH_YCSB
#include "index/masstree_beta/include/masstree_beta_wrapper.h"
#endif // BENCH_YCSB

#include "gflags/gflags.h"
#include "glog/logging.h"

namespace ccbench {

class kohler_masstree {
public:
    static void* find_record(std::string_view key);

    static Status insert_record(std::string_view key, Record* record);

private:
    static inline masstree_wrapper<Record> MTDB;
};

}
