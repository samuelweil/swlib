cmake_minimum_required(VERSION 3.16)
project(RustLike)

find_package(Catch2 3 REQUIRED)
# These tests can use the Catch2-provided main
add_executable(tests src/test.cpp)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)