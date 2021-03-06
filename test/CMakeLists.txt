file(GLOB SILO_SOURCES
        "${PROJECT_SOURCE_DIR}/src/cc/silo/epoch.cpp"
        "${PROJECT_SOURCE_DIR}/src/cc/silo/garbage_collection.cpp"
        "${PROJECT_SOURCE_DIR}/src/cc/silo/interface/interface_delete.cpp"
        "${PROJECT_SOURCE_DIR}/src/cc/silo/interface/interface_helper.cpp"
        "${PROJECT_SOURCE_DIR}/src/cc/silo/interface/interface_scan.cpp"
        "${PROJECT_SOURCE_DIR}/src/cc/silo/interface/interface_search.cpp"
        "${PROJECT_SOURCE_DIR}/src/cc/silo/interface/interface_termination.cpp"
        "${PROJECT_SOURCE_DIR}/src/cc/silo/interface/interface_update_insert.cpp"
        "${PROJECT_SOURCE_DIR}/src/cc/silo/log.cpp"
        "${PROJECT_SOURCE_DIR}/src/cc/silo/scheme.cpp"
        "${PROJECT_SOURCE_DIR}/src/cc/silo/session_info.cpp"
        "${PROJECT_SOURCE_DIR}/src/cc/silo/session_info_table.cpp"
        "${PROJECT_SOURCE_DIR}/src/cc/silo/tid.cpp"
        "${PROJECT_SOURCE_DIR}/src/index/masstree_beta/masstree_beta_wrapper.cpp"
        )

file(GLOB TEST_SOURCES
        "aligned_allocator_test.cpp"
        "scheme_global_test.cpp"
        "unit_test.cpp"
        )

if (BENCH_TPCC)
    file(GLOB TPCC_TEST_SOURCES
            "tpcc/tpcc_initializer_test.cpp"
            "tpcc/tpcc_tables_test.cpp"
            "tpcc/tpcc_util_test.cpp"
            )
    set(TEST_SOURCES ${TEST_SOURCES} ${TPCC_TEST_SOURCES})
endif ()

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

foreach (src IN LISTS TEST_SOURCES)
    get_filename_component(fname "${src}" NAME_WE)
    if (fname MATCHES "test$")
        set(test_name "${fname}.exe")

        if (fname MATCHES "unit_test")
            add_executable(
                    ${test_name}
                    ${src}
                    ${SILO_SOURCES}
            )
        elseif ((fname MATCHES "tpcc_tables_test") OR (fname MATCHES "tpcc_initializer_test"))
            add_executable(
                    ${test_name}
                    ${src}
                    ${PROJECT_SOURCE_DIR}/src/cc/silo/epoch.cpp
                    ${PROJECT_SOURCE_DIR}/src/index/masstree_beta/masstree_beta_wrapper.cpp
            )
        else ()
            add_executable(
                    ${test_name}
                    ${src}
            )
        endif ()

        target_include_directories(${test_name}
                PRIVATE ${PROJECT_SOURCE_DIR}
                PRIVATE ${PROJECT_SOURCE_DIR}/benchmark/include
                PRIVATE ${PROJECT_SOURCE_DIR}/benchmark/tpcc/include
                PRIVATE ${PROJECT_SOURCE_DIR}/src
                PRIVATE ${PROJECT_SOURCE_DIR}/src/include
                PRIVATE ${PROJECT_SOURCE_DIR}/third_party
                PRIVATE ${PROJECT_SOURCE_DIR}/third_party/googletest/googletest/include
                )

        target_link_libraries(${test_name}
                Boost::filesystem
                gflags::gflags
                ${PROJECT_SOURCE_DIR}/third_party/masstree/libkohler_masstree_json.a
                ${PROJECT_SOURCE_DIR}/third_party/googletest/build/lib/libgtest.a
                ${PROJECT_SOURCE_DIR}/third_party/googletest/build/lib/libgtest_main.a
                Threads::Threads
                )
        set_compile_options(${test_name})
        add_test(
                NAME ${test_name}
                COMMAND ${test_name} --gtest_output=xml:${test_name}_gtest_result.xml)
    endif ()
endforeach ()
