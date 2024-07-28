#pragma once

#include "GArgs-Help/CommandKey.hpp"
#include "GArgs-Help/FlagKey.hpp"
#include "GArgs-Help/Structure.hpp"
#include <map>
#include <string>
#include <vector>

namespace GArgs {
class ArgumentsParser : public std::map<std::string, std::string> {
public:
  ArgumentsParser(const std::string &program_title, const std::string &version,
                  const bool &allow_relative_path = false);
  ArgumentsParser(ArgumentsParser &&) = default;
  ArgumentsParser(const ArgumentsParser &) = default;
  ArgumentsParser &operator=(ArgumentsParser &&) = default;
  ArgumentsParser &operator=(const ArgumentsParser &) = default;
  ~ArgumentsParser();

  Structure &AddStructure(const std::string &structure_str);
  Structure &ClearStructure();

  void ParseArgs(int argc, char *argv[]);

  void DisplayHelp();

  void AddFlag(const FlagKey &flag);
  void AddCommand(const CommandKey &command);

  bool Contains(const std::string &key, const std::string &value);

private:
  Structure m_structure;

  std::vector<FlagKey> m_flags;
  std::vector<CommandKey> m_commands;

  std::string m_name;
  std::string m_version;
  bool m_allowRelative;

  void _UpdateParserMap();
};

} // namespace GArgs
