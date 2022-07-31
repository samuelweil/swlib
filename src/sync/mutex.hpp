#pragma once

#include <memory>
#include <stdexcept>

#include "not_implemented.hpp"

namespace sweil {
namespace sync {

// Forward declarations
template <typename T>
class Mutex;
template <typename T>
auto thread_safe() -> Mutex<T>;

template <typename T>
class Mutex {
 private:
  Mutex() : _ptr(std::make_shared<T>()) {}
  std::shared_ptr<T> _ptr;
  friend Mutex<T> thread_safe<T>();
};

template <typename T>
auto thread_safe() -> Mutex<T> {
  return Mutex<T>();
}

}  // namespace sync
}  // namespace sweil