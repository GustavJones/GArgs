#pragma once

#include <string>

namespace GArgs {
class CommandKey {
public:
  CommandKey(const std::string &parent_str, const std::string &cmd_str,
             const std::string &help_str);
  CommandKey(CommandKey &&) = default;
  CommandKey(const CommandKey &) = default;
  CommandKey &operator=(CommandKey &&) = default;
  CommandKey &operator=(const CommandKey &) = default;
  ~CommandKey();

  std::string parent;
  std::string cmd;
  std::string help;
};
} // namespace GArgs
