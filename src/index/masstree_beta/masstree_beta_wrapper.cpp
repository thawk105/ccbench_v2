/**
 * @file masstree_wrapper.cc
 * @brief implement about masstree_wrapper
 */

#include <bitset>

#include "include/masstree_beta_wrapper.h"

#include "cpu.h"
#include "scheme_global.h"

// about bench
#ifdef BENCH_TPCC
#include "benchmark/tpcc/include/tpcc_tables.hpp"
using namespace ccbench::TPCC;
#endif
#ifdef BENCH_YCSB

#include "benchmark/include/ycsb_table.h"

#endif

volatile mrcu_epoch_type active_epoch = 1;          // NOLINT
volatile uint64_t globalepoch = 1;                  // NOLINT
[[maybe_unused]] volatile bool recovering = false;  // NOLINT

namespace ccbench {

#ifdef BENCH_TPCC
Status kohler_masstree::insert_record(Storage st, std::string_view key, Record* record) {
    masstree_wrapper<Record>::thread_init(cached_sched_getcpu());
    Status insert_result(get_mtdb(st).insert_value(key, record));
    return insert_result;
}

void* kohler_masstree::find_record(Storage st, std::string_view key) {
    masstree_wrapper<Record>::thread_init(cached_sched_getcpu());
    return get_mtdb(st).get_value(key.data(), key.size());
}
#endif

#ifdef BENCH_YCSB

Status kohler_masstree::insert_record(std::string_view const key, Record* const record) {
    masstree_wrapper<Record>::thread_init(cached_sched_getcpu());
    Status insert_result(MTDB.insert_value(key, record));
    return insert_result;
}

void* kohler_masstree::find_record(std::string_view const key) {
    masstree_wrapper<Record>::thread_init(cached_sched_getcpu());
    return MTDB.get_value(key.data(), key.size());
}

void
kohler_masstree::scan(const std::string_view l_key, const bool l_exclusive, const std::string_view r_key,
                      const bool r_exclusive, std::vector<const Record*>* res, const bool limited_scan) {
    masstree_wrapper<Record>::thread_init(cached_sched_getcpu());
    return MTDB.scan(l_key.empty() ? nullptr : l_key.data(), l_key.size(), l_exclusive,
                     r_key.empty() ? nullptr : r_key.data(), r_key.size(), r_exclusive, res,
                     limited_scan);
}

#endif

}  // namespace shirakami
