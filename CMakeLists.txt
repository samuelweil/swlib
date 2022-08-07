cmake_minimum_required(VERSION 3.16)
project(RustLike)

find_package(Catch2 3 REQUIRED)

file(GLOB_RECURSE SOURCES src/*.cpp)

add_executable(tests ${SOURCES})

set_property(TARGET tests PROPERTY CXX_STANDARD 20)

include_directories(tests src)

target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)

