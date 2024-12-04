#pragma once

#include "GArgs-Help/Argument.hpp"
#include "GArgs-Help/Key.hpp"
#include <vector>

namespace GArgs {
class Structure : public std::vector<Argument *> {
public:
  Structure();
  Structure(Structure &&) = default;
  Structure(const Structure &) = default;
  Structure &operator=(Structure &&) = default;
  Structure &operator=(const Structure &) = default;
  ~Structure();

  void Parse(const std::string &structure_str);
  std::string HelpMessage(const std::string &title,
                          const std::string &version) const;

  void AddKey(const Key &key);

private:
  void _ParseStructureArgument(
      const std::string &argument_str, std::string &argument_name,
      std::vector<std::pair<std::string, std::string>> &argument_properties);

  void _ParseStructureProperty(const std::string &property_str,
                               std::string &property_name,
                               std::string &property_value);

  void
  _AddArgumentToStructure(const std::string &argument_name,
                          const std::vector<std::pair<std::string, std::string>>
                              &argument_properties);

private:
  std::vector<GArgs::Key> m_keys;
};
} // namespace GArgs
