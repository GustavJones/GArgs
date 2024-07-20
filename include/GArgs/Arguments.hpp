#pragma once

#include <string>

namespace GArgs {
class Arguments {
public:
  Arguments();
  Arguments(Arguments &&) = default;
  Arguments(const Arguments &) = default;
  Arguments &operator=(Arguments &&) = default;
  Arguments &operator=(const Arguments &) = default;
  ~Arguments();

  void add_structure(const std::string &structure_str);

  void parse_args(int argc, char *argv[]);

private:
};

} // namespace GArgs
