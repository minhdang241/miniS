cmake_minimum_required(VERSION 3.31)
project(mini_sqlite)

set(CMAKE_CXX_STANDARD 20)

set(CORE_SOURCES
        src/tokenizer.cpp
        src/parser.cpp
        src/command_handler.cpp
        src/table.cpp
        src/bplus_tree.cpp
        src/bplus_tree_leaf_node.cpp
        src/bplus_tree_internal_node.cpp
        src/bplus_tree_node.cpp
)

add_library(CORE_SOURCES_LIB ${CORE_SOURCES})
target_include_directories(CORE_SOURCES_LIB PUBLIC include)

add_executable(mini_sqlite
        ${CORE_SOURCES}
        src/main.cpp
)
target_include_directories(mini_sqlite PRIVATE include)

# Testing setup
enable_testing()
add_library(catch2_main lib/catch2_main.cpp)
target_include_directories(catch2_main PUBLIC lib)

# Add test executables
add_executable(test_parser test/test_parser.cpp)
target_link_libraries(test_parser PRIVATE CORE_SOURCES_LIB catch2_main)
add_test(test_parser test_parser)

add_executable(test_tokenizer test/test_tokenizer.cpp)
target_link_libraries(test_tokenizer PRIVATE CORE_SOURCES_LIB catch2_main)
add_test(test_tokenizer test_tokenizer)

add_executable(test_table test/test_table.cpp)
target_link_libraries(test_table PRIVATE CORE_SOURCES_LIB catch2_main)
add_test(test_table test_table)

add_executable(test_disk_manager test/test_disk_manager.cpp)
target_link_libraries(test_disk_manager PRIVATE CORE_SOURCES_LIB catch2_main)
add_test(test_disk_manager test_disk_manager)

add_executable(test_btree test/test_btree.cpp)
target_link_libraries(test_btree PRIVATE CORE_SOURCES_LIB catch2_main)
add_test(test_btree test_btree)
