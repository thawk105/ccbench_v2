#include <stdio.h>
#include <xmmintrin.h>
#include <sys/types.h>  // syscall(SYS_gettid),

#include <bitset>
#include <iostream>

#include "atomic_wrapper.h"
#include "common.hh"
#include "include/util.hh"

#include "util.hh"

namespace ccbench {

void displayParameter() {
  std::cout << "#FLAGS_thread_num:\t" << FLAGS_thread_num << std::endl;
  std::cout << "#FLAGS_clocks_per_us:\t" << FLAGS_clocks_per_us << std::endl;
  std::cout << "#FLAGS_epoch_time:\t" << FLAGS_epoch_time << std::endl;
  std::cout << "#FLAGS_extime:\t\t" << FLAGS_extime << std::endl;
  std::cout << "#FLAGS_num_wh:\t\t" << FLAGS_num_wh << std::endl;
  std::cout << "#FLAGS_perc_payment:\t\t" << FLAGS_perc_payment << std::endl;
  std::cout << "#FLAGS_perc_order_status:\t" << FLAGS_perc_order_status << std::endl;
  std::cout << "#FLAGS_perc_delivery:\t\t" << FLAGS_perc_delivery << std::endl;
  std::cout << "#FLAGS_perc_stock_level:\t" << FLAGS_perc_stock_level << std::endl;
}

void chkArg() {
  displayParameter();

  if (FLAGS_perc_payment > 100) {
    std::cout << "FLAGS_perc_payment must be 0..100 ..." << std::endl;
    std::abort();
  }
  if (FLAGS_perc_order_status > 100) {
    std::cout << "FLAGS_perc_order_status must be 0..100 ..." << std::endl;
    std::abort();
  }
  if (FLAGS_perc_delivery > 100) {
    std::cout << "FLAGS_perc_delivery must be 0..100 ..." << std::endl;
    std::abort();
  }
  if (FLAGS_perc_stock_level > 100) {
    std::cout << "FLAGS_perc_stock_level must be 0..100 ..." << std::endl;
    std::abort();
  }
  if (FLAGS_perc_payment + FLAGS_perc_order_status
      + FLAGS_perc_delivery + FLAGS_perc_stock_level > 100) {
    std::cout << "sum of FLAGS_perc_[payment,order_status,delivery,stock_level] must be 0..100 ..." << std::endl;
    std::abort();
  }
}

void waitForReady(const std::vector<char> &readys) {
  while (!isReady(readys)) {
    _mm_pause();
  }
}

}
