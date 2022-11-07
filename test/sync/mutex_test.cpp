#include <sync/mutex.hpp>

#include <atomic>
#include <chrono>
#include <catch2/catch_test_macros.hpp>
#include <thread>

#include "../test_class.hpp"

using namespace sweil::sync;
using namespace std::chrono_literals;

const auto LABELS = "[all,sync,mutex]";

TEST_CASE("Default constructed mutex", LABELS) {  
  REQUIRE_NOTHROW(make_thread_safe<TestClass>());
}

TEST_CASE("Pass through constructed mutex", LABELS) {
  REQUIRE_NOTHROW(make_thread_safe<TestClass>(12));
}

TEST_CASE("Access value through lock", LABELS) {
  auto mutex = make_thread_safe<TestClass>(13);

  auto lock = mutex.lock();
  REQUIRE(lock->value() == 13);

  *lock = TestClass(15);
  REQUIRE(lock->value() == 15);

  lock->value(123);
  REQUIRE(lock->value() == 123);
}

TEST_CASE("Prevent access when locked", LABELS) {
  const int INITIAL_VALUE = 13;
  const int UPDATED_VALUE = 15;
  auto mutex = make_thread_safe<TestClass>(INITIAL_VALUE);

  std::atomic_bool done(false);
  std::atomic_bool release(false);

  std::thread worker;

  {
    auto lock = mutex.lock();

    worker = std::thread([&]() {
      // Should be blocking here
      auto worker_lock = mutex.lock();
      worker_lock->value(UPDATED_VALUE);
      done = true;
    });

    std::this_thread::sleep_for(100ms);

    REQUIRE_FALSE(done.load());
    REQUIRE(lock->value() == INITIAL_VALUE);
  }

  worker.join();
  REQUIRE(done.load());
  REQUIRE(mutex.lock()->value() == UPDATED_VALUE);
}
