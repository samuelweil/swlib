cmake_minimum_required(VERSION 3.16)

project(swlib)

set(LIB_FILES
    include/sync/mutex.hpp
)

add_library(swlib INTERFACE ${LIB_FILES})
target_compile_features(swlib INTERFACE cxx_std_20)

target_include_directories(swlib INTERFACE 
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

add_subdirectory(test)