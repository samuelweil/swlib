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
  struct Container {
    template <typename... Params>
    Container(Params&&... params) : value(T(std::forward<Params>(params)...)) {}

    T value;
    std::shared_mutex mutex;
  };

  using mutex_t = std::shared_mutex;
  using lock_t = std::unique_lock<mutex_t>;
  using container_t = std::shared_ptr<Container>;

 public:
  template <typename... Params>
  Mutex(Params&&... params)
      : _container_ptr(
            std::make_shared<Container>(std::forward<Params>(params)...)) {}

  class Lock {
   public:
    T* operator->() { return &(_ref->value); }
    T& operator*() { return _ref->value; }

    ~Lock() = default;

   private:
    Lock(container_t& container) : _ref(container), _lock(container->mutex) {}

    Lock(const Lock&) = delete;
    Lock(Lock&&) = default;

    Lock& operator=(const Lock& lock) = delete;
    Lock& operator=(Lock&& lock) = default;

    container_t _ref;
    lock_t _lock;

    friend class Mutex;
  };

  Lock lock() { return Lock(_container_ptr); }

  container_t _container_ptr;
};

template <typename T, typename... Params>
auto make_thread_safe(Params&&... params) -> Mutex<T> {
  return Mutex<T>(std::forward<Params>(params)...);
}

}  // namespace sync
}  // namespace sweil