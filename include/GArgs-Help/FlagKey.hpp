#pragma once

#include <string>

namespace GArgs {
class FlagKey {
public:
  FlagKey(const std::string &parent_str, const std::string &flag_str,
          const std::string &help_str);
  FlagKey(FlagKey &&) = default;
  FlagKey(const FlagKey &) = default;
  FlagKey &operator=(FlagKey &&) = default;
  FlagKey &operator=(const FlagKey &) = default;
  ~FlagKey();

  std::string parent;
  std::string flag;
  std::string help;
};
} // namespace GArgs
