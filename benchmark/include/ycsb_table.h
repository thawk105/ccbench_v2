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

    static Status remove_value(std::string_view key) {
        return MTDB.remove_value(key.data(), key.size());
    }

    static void
    scan(std::string_view l_key, bool l_exclusive, std::string_view r_key, bool r_exclusive,
         std::vector<const Record*>* res,
         bool limited_scan);

private:
    static inline masstree_wrapper<Record> MTDB;
};

}
