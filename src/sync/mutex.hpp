#pragma once

#include <memory>
#include <mutex>
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
  using ptr_t = std::shared_ptr<T>;
  using mutex_t = std::shared_ptr<std::mutex>;

 public:
  Mutex(ptr_t&& ptr) : _ptr(ptr), _mutex(std::make_shared<std::mutex>()) {}

 private:
  ptr_t _ptr;
  mutex_t _mutex;
};

template <typename T, typename... Params>
auto make_thread_safe(Params&&... params) -> Mutex<T> {
  auto ptr = std::make_shared<T>(std::forward<Params>(params)...);
  return Mutex<T>(std::move(ptr));
}

}  // namespace sync
}  // namespace sweil