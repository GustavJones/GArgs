#pragma once

#include "GArgs-Help/Key.hpp"
#include "GArgs-Help/Structure.hpp"
#include <map>
#include <string>
#include <vector>

namespace GArgs {
class ArgumentsParser : public std::map<std::string, std::vector<std::string>> {
public:
  ArgumentsParser(const std::string &program_title, const std::string &version,
                  const bool &allow_relative_path = true);
  ArgumentsParser(ArgumentsParser &&) = default;
  ArgumentsParser(const ArgumentsParser &) = default;
  ArgumentsParser &operator=(ArgumentsParser &&) = default;
  ArgumentsParser &operator=(const ArgumentsParser &) = default;
  ~ArgumentsParser();

  const Structure &AddStructure(const std::string &structure_str);
  const Structure &ClearStructure();

  void ParseArgs(int argc, char *argv[]);
  void DisplayHelp() const;
  void AddKey(const Key &key);
  bool Contains(const std::string &key, const std::string &value) const;

private:
  Structure m_structure;

  std::string m_name;
  std::string m_version;
  bool m_allowRelative;

  void _UpdateParserMap();
};

} // namespace GArgs
