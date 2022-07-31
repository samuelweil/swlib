#include "./mutex.hpp"

#include <catch2/catch_test_macros.hpp>

#include "./test_class.hpp"

using namespace sweil::sync;

TEST_CASE("Mutex constructor", "[all,sync,mutex]") {
  const auto mutex = thread_safe<TestClass>();
}