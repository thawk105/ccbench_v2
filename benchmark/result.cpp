#include "include/result.hh"
#include "include/common.hh"

using namespace std;

alignas(CACHE_LINE_SIZE) std::vector<Result> SiloResult;

void initResult() { SiloResult.resize(FLAGS_thread_num); }
