/**
 * @file garbage_collection.cpp
 * @brief about garbage collection.
 */

// about index
#include "index/masstree_beta/include/masstree_beta_wrapper.h"

// about cc
#include "cc/silo/include/garbage_collection.h"
#include "cc/silo/include/session_info.h"

// about bench
#include "benchmark/tpcc/include/tpcc_tables.hpp"

namespace ccbench::garbage_collection {

[[maybe_unused]] void release_all_heap_objects() {
  remove_all_leaf_from_mt_db_and_release();
  delete_all_garbage_records();
  delete_all_garbage_values();
}

void remove_all_leaf_from_mt_db_and_release() {
  std::vector<const Record *> scan_res;
#ifdef BENCH_TPCC
  for (std::size_t i = 0; i < ccbench::TPCC::kohler_masstree::db_length; ++i) {
    ccbench::TPCC::kohler_masstree::get_mtdb(static_cast<Storage>(i)).scan(nullptr, 0, false, nullptr, 0, false,
                                                            &scan_res, false);  // NOLINT
    for (auto &&itr : scan_res) {
      std::string_view key_view = itr->get_tuple().get_key();
      ccbench::TPCC::kohler_masstree::get_mtdb(static_cast<Storage>(i)).remove_value(key_view.data(), key_view.size());
      if (i == static_cast<int>(Storage::SECONDARY)) {
        std::vector<void *> *ctn_ptr;
        memcpy(&ctn_ptr,
               reinterpret_cast<void *>(const_cast<char *>(itr->get_tuple().get_val().data())), 8);
        delete ctn_ptr;
      }
      delete itr;  // NOLINT
    }

    /**
     * check whether index_kohler_masstree::get_mtdb() is empty.
     */
    scan_res.clear();
    ccbench::TPCC::kohler_masstree::get_mtdb(static_cast<Storage>(i)).scan(nullptr, 0, false, nullptr, 0, false,
                                                            &scan_res, false);  // NOLINT
    if (!scan_res.empty()) std::abort();
  }
#endif
}

void delete_all_garbage_records() {
  for (auto i = 0; i < KVS_NUMBER_OF_LOGICAL_CORES; ++i) {
    RecPtrContainer& q = get_garbage_records_at(i);
    while (!q.empty()) {
      Record* rec = q.front();
      delete rec; // NOLINT
      q.pop_front();
    }
  }
}

void delete_all_garbage_values() {
  for (auto i = 0; i < KVS_NUMBER_OF_LOGICAL_CORES; ++i) {
    ObjEpochContainer& q = get_garbage_values_at(i);
    q.clear(); // HeapObject instances are automatically deallocated.
  }
}

}  // namespace ccbench::garbage_collection
