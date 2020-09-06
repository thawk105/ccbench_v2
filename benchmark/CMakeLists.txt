file(GLOB SILO_SOURCES
        "result.cpp"
        "{PROJECT_SOURCE_DIR}/src/util.cc"
        "{PROJECT_SOURCE_DIR}/src/epoch.cpp"
        "{PROJECT_SOURCE_DIR}/src/garbage_collection.cpp"
        "{PROJECT_SOURCE_DIR}/src/index/masstree_beta/masstree_beta_wrapper.cpp"
        "{PROJECT_SOURCE_DIR}/src/interface/interface_delete.cpp"
        "{PROJECT_SOURCE_DIR}/src/interface/interface_helper.cpp"
        "{PROJECT_SOURCE_DIR}/src/interface/interface_scan.cpp"
        "{PROJECT_SOURCE_DIR}/src/interface/interface_search.cpp"
        "{PROJECT_SOURCE_DIR}/src/interface/interface_termination.cpp"
        "{PROJECT_SOURCE_DIR}/src/interface/interface_update_insert.cpp"
        "{PROJECT_SOURCE_DIR}/src/log.cpp"
        "{PROJECT_SOURCE_DIR}/src/result.cc"
        "{PROJECT_SOURCE_DIR}/src/scheme.cpp"
        "{PROJECT_SOURCE_DIR}/src/session_info.cpp"
        "{PROJECT_SOURCE_DIR}/src/session_info_table.cpp"
        "{PROJECT_SOURCE_DIR}/src/tid.cpp"
        "{PROJECT_SOURCE_DIR}/src/util.cc"
        "{PROJECT_SOURCE_DIR}/src/util.cpp"
        )

file(GLOB TPCC_SOURCES
        "tpcc/neworder.cpp"
        "tpcc/payment.cpp"
        "tpcc/tpcc_query.cpp"
        )
add_executable(bench.exe ${SILO_SOURCES} bench.cpp ${TPCC_SOURCES})

set_compile_options(bench.exe)

target_include_directories(bench.exe
        PRIVATE include
        PRIVATE ${PROJECT_SOURCE_DIR}
        PRIVATE ${PROJECT_SOURCE_DIR}/third_party
        PRIVATE ${PROJECT_SOURCE_DIR}/src/include
        PRIVATE ${PROJECT_SOURCE_DIR}/src/index/masstree_beta/include
        PRIVATE ${PROJECT_SOURCE_DIR}/src/interface
        PRIVATE ${PROJECT_SOURCE_DIR}/tpcc
        )

target_link_libraries(bench.exe
        Boost::filesystem
        gflags::gflags
        ${PROJECT_SOURCE_DIR}/third_party/mimalloc/out/release/libmimalloc.a
        ${PROJECT_SOURCE_DIR}/third_party/masstree/libkohler_masstree_json.a
        Threads::Threads
        )

if (CMAKE_SYSTEM_NAME MATCHES "Linux")
    add_definitions(-DCCBENCH_LINUX)
endif ()

cmake_host_system_information(RESULT cores QUERY NUMBER_OF_LOGICAL_CORES)
add_definitions(-DKVS_EPOCH_TIME=40)
add_definitions(-DKVS_NUMBER_OF_LOGICAL_CORES=${cores})
add_definitions(-DKVS_MAX_PARALLEL_THREADS=500)
add_definitions(-DKVS_MAX_KEY_LENGTH=1000)
add_definitions(-DKVS_LOG_GC_THRESHOLD=1)
add_definitions(-DPROJECT_ROOT=${PROJECT_SOURCE_DIR})

