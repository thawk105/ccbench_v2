cmake_minimum_required(VERSION 3.10)

project(ccbench_v2
        VERSION 0.0.1
        DESCRIPTION "ccbench v2"
        LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

option(ENABLE_SANITIZER "enable sanitizer on debug build" ON)
option(ENABLE_UB_SANITIZER "enable undefined behavior sanitizer on debug build" OFF)
option(ENABLE_COVERAGE "enable coverage on debug build" OFF)

# benchmark
option(BENCH_TPCC "It builds benchmark/bench.cpp as TPC-C benchmark." ON)
option(BENCH_YCSB "It builds benchmark/bench.cpp as YCSB benchmark." OFF)

set(bench_set 0)
if (BENCH_TPCC)
    set(bench_set 1)
    add_definitions(-DBENCH_TPCC)
endif ()

if (BENCH_YCSB)
    if (bench_set)
        message(FATAL_ERROR "It can select only one bench (TPC-C or YCSB).")
    endif ()
    add_definitions(-DBENCH_YCSB)
endif ()

find_package(Doxygen)
find_package(Threads REQUIRED)
find_package(gflags REQUIRED)
find_package(glog REQUIRED)
find_package(Boost
        COMPONENTS filesystem)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)
include(CompileOptions)

enable_testing()
add_subdirectory(benchmark)
add_subdirectory(test)

