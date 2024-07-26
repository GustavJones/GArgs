#include "GArgs/ArgumentsException.hpp"
#include <stdexcept>

namespace GArgs {
ArgumentsException::ArgumentsException(const std::string &error)
    : std::runtime_error(error) {}

ArgumentsException::~ArgumentsException() {}
} // namespace GArgs
