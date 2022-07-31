#include <stdexcept>
#include <string>
#define NOT_IMPLEMENTED()                              \
  throw std::runtime_error(std::string(__FUNCTION__) + \
                           std::string(" is not implemented"))