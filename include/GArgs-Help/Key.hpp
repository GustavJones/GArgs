#pragma once

#include <string>

namespace GArgs {
class Key {
public:
  Key(const std::string &parent_str, const std::string &key_str,
      const std::string &help_str);
  Key(Key &&) = default;
  Key(const Key &) = default;
  Key &operator=(Key &&) = default;
  Key &operator=(const Key &) = default;
  ~Key();

  std::string parent;
  std::string key;
  std::string help;
};
} // namespace GArgs
