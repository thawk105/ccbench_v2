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

volatile mrcu_epoch_type active_epoch = 1;          // NOLINT
volatile uint64_t globalepoch = 1;                  // NOLINT
[[maybe_unused]] volatile bool recovering = false;  // NOLINT

namespace ccbench {

#ifdef BENCH_TPCC
Status kohler_masstree::insert_record(Storage st, std::string_view key, Record *record) {
  masstree_wrapper<Record>::thread_init(cached_sched_getcpu());
  Status insert_result(get_mtdb(st).insert_value(key, record));
  return insert_result;
}

void * kohler_masstree::find_record(Storage st, std::string_view key) {
  masstree_wrapper<Record>::thread_init(cached_sched_getcpu());
  return get_mtdb(st).get_value(key.data(), key.size());
}

#endif

}  // namespace shirakami
