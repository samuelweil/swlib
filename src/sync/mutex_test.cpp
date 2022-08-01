#include "./mutex.hpp"

#include <catch2/catch_test_macros.hpp>

#include "./test_class.hpp"

using namespace sweil::sync;

const auto LABELS = "[all,sync,mutex]";

TEST_CASE("Default constructed mutex", LABELS) {
  auto mutex = make_thread_safe<TestClass>();
}

TEST_CASE("Pass through constructed mutex") {
  auto mutex = make_thread_safe<TestClass>(12);
}