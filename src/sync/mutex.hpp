#pragma once

#include <stdexcept>

#include "not_implemented.hpp"

namespace sweil {
namespace sync {

template <typename T>
class Mutex {};

template <typename T>
auto thread_safe() -> Mutex<T> {
  NOT_IMPLEMENTED();
}

}  // namespace sync
}  // namespace sweil