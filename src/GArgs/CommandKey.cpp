#include "GArgs/CommandKey.hpp"

namespace GArgs {

CommandKey::CommandKey(const std::string &parent_str,
                       const std::string &cmd_str, const std::string &help_str)
    : parent(parent_str), cmd(cmd_str), help(help_str) {}

CommandKey::~CommandKey() {}
} // namespace GArgs
