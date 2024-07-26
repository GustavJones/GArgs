#pragma once

#include <string>

namespace GArgs {

enum ArgumentTypes {
  Command,
  PositionalArg,
};

class Argument {
public:
  virtual ~Argument() {};

  std::string name;
  std::string help;
  std::string value;

  ArgumentTypes type;

  bool required;
};

} // namespace GArgs
