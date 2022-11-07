find_package(Catch2 3 REQUIRED)

add_executable(unit_tests sync/mutex_test.cpp)

target_link_libraries(unit_tests PRIVATE swlib)
target_link_libraries(unit_tests PRIVATE Catch2::Catch2WithMain)

include(CTest)
include(Catch)
catch_discover_tests(unit_tests
    REPORTER JUnit
    OUTPUT_DIR unit_test_results
    OUTPUT_SUFFIX .xml
)