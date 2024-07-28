#include "GArgs-Help/FlagKey.hpp"

namespace GArgs {
FlagKey::FlagKey(const std::string &parent_str, const std::string &flag_str,
                 const std::string &help_str)
    : parent(parent_str), flag(flag_str), help(help_str) {
  if (flag[0] != '-') {
    flag = "--" + flag;
  }
}

FlagKey::~FlagKey() {}
} // namespace GArgs
