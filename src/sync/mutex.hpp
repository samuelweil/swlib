#pragma once

#include <memory>
#include <mutex>
#include <shared_mutex>
#include <stdexcept>

namespace sweil {
namespace sync {

// Forward declarations
template <typename T>
class Mutex;
template <typename T, typename... Params>
auto make_thread_safe(Params&&...) -> Mutex<T>;

template <typename T>
class Mutex {
  using value_ptr = std::shared_ptr<T>;
  using mutex_t = std::shared_mutex;
  using mutex_ptr = std::shared_ptr<mutex_t>;
  using lock_t = std::unique_lock<mutex_t>;

 public:
  Mutex(value_ptr&& ptr) : _ptr(ptr), _mutex(std::make_shared<mutex_t>()) {}

  class Lock {
   public:
    Lock(Lock&& lock)
        : _value(std::move(lock._value)),
          _lock_guard(std::move(lock._lock_guard)) {}

    T* operator->() {
      auto raw_value = _value.get();
      return raw_value;
    }

    T& operator*() { return *_value; }

   private:
    Lock(value_ptr& value, mutex_t& mutex)
        : _value(value), _lock_guard(mutex) {}

    std::lock_guard<mutex_t> _lock_guard;
    value_ptr _value;

    friend class Mutex;
  };

  Lock lock() { return Lock(_ptr, *_mutex); }

 private:
  value_ptr _ptr;
  mutex_ptr _mutex;
};

template <typename T, typename... Params>
auto make_thread_safe(Params&&... params) -> Mutex<T> {
  auto ptr = std::make_shared<T>(std::forward<Params>(params)...);
  return Mutex<T>(std::move(ptr));
}

}  // namespace sync
}  // namespace sweil