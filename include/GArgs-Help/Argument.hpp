#pragma once

#include <string>
#include <vector>

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
  std::vector<std::string> values;
  std::string argumentFilter;
  unsigned int valueAmount;

  ArgumentTypes type;

  bool required;
};

} // namespace GArgs
