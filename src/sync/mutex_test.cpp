#include "./mutex.hpp"

#include <catch2/catch_test_macros.hpp>

#include "./test_class.hpp"

using namespace sweil::sync;

const auto LABELS = "[all,sync,mutex]";

TEST_CASE("Default constructed mutex", LABELS) {
  auto mutex = make_thread_safe<TestClass>();
}

TEST_CASE("Pass through constructed mutex", LABELS) {
  auto mutex = make_thread_safe<TestClass>(12);
}

TEST_CASE("Access value through lock", LABELS) {
  auto mutex = make_thread_safe<TestClass>(13);

  auto lock = mutex.lock();
  assert(lock->value() == 13);

  *lock = TestClass(15);
  assert(lock->value() == 15);

  lock->value(123);
  assert(lock->value() == 123);
}