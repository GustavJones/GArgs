#pragma once

#include <string>

namespace GArgs {

enum ArgumentTypes {
  Flag,
  Command,
  PositionalArg,
};

class Argument {
public:
  virtual ~Argument() {};

  std::string name;
  std::string help;
  std::string value;
  std::string argumentFilter;
  unsigned int valueAmount;

  ArgumentTypes type;

  bool required;
};

} // namespace GArgs
