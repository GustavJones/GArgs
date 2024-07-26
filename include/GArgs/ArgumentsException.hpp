#pragma once

#include <stdexcept>

namespace GArgs {
class ArgumentsException : public std::runtime_error {
public:
  ArgumentsException(const std::string &error);
  ArgumentsException(ArgumentsException &&) = default;
  ArgumentsException(const ArgumentsException &) = default;
  ArgumentsException &operator=(ArgumentsException &&) = default;
  ArgumentsException &operator=(const ArgumentsException &) = default;
  ~ArgumentsException();

private:
};

} // namespace GArgs
