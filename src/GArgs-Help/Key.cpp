#include "GArgs-Help/Key.hpp"

namespace GArgs {

Key::Key(const std::string &parent_str, const std::string &key_str,
         const std::string &help_str)
    : parent(parent_str), key(key_str), help(help_str) {}

Key::~Key() {}
} // namespace GArgs
