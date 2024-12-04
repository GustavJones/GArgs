#include "GArgs-Parser/ArgumentsParser.hpp"
#include "GArgs-Core/ArgumentsException.hpp"
#include "GArgs-Help/Argument.hpp"
#include <iostream>

namespace GArgs {
ArgumentsParser::ArgumentsParser(const std::string &program_title,
                                 const std::string &version,
                                 const bool &allow_relative_path)
    : m_name(program_title), m_version(version),
      m_allowRelative(allow_relative_path) {}

ArgumentsParser::~ArgumentsParser() {}

void ArgumentsParser::AddKey(const Key &key) { m_structure.AddKey(key); }
void ArgumentsParser::DisplayHelp() const {
  std::cout << m_structure.HelpMessage(m_name, m_version) << std::endl;
}

const Structure &
ArgumentsParser::AddStructure(const std::string &structure_str) {
  m_structure.Parse(structure_str);
  _UpdateParserMap();
  return m_structure;
}

const Structure &ArgumentsParser::ClearStructure() {
  for (auto &item : m_structure) {
    delete item;
  }
  m_structure.clear();
  _UpdateParserMap();
  return m_structure;
}

void ArgumentsParser::ParseArgs(int argc, char *argv[]) {
  int i = 1;
  std::string argument;

  // Relative Path Running Check
  if (argv[0] != m_name && !m_allowRelative) {
    throw GArgs::ArgumentsException("Program run from relative path");
  }

  for (auto &arg : m_structure) {
    if (i >= argc) {
      break;
    }

    argument = argv[i];

    if (arg->valueAmount == 0) {
      while (argument.find(arg->argumentFilter) == 0) {
        arg->values.push_back(argument);
        i++;

        if (i >= argc) {
          break;
        }

        argument = argv[i];
      }
    } else {

      if (i >= argc) {
        break;
      }
      argument = argv[i];

      while (arg->values.size() < arg->valueAmount) {
        arg->values.push_back(argument);
        i++;

        if (i >= argc) {
          break;
        }

        argument = argv[i];
      }
    }
  }

  _UpdateParserMap();
}

void ArgumentsParser::_UpdateParserMap() {
  int i = 0;

  this->clear();
  for (const auto &arg : m_structure) {
    (*this)[arg->name] = arg->values;
  }
}

bool ArgumentsParser::Contains(const std::string &key,
                               const std::string &value) const {
  std::vector<std::string> values;
  bool found = false;
  for(const auto &k : (*this)) {
    if (key == k.first) {
      values = k.second;     
    }
  }

  for (const auto &v : values) {
    if (v.find(value) != v.npos) {
      found = true;
    }
  }
  return found;
}
} // namespace GArgs
