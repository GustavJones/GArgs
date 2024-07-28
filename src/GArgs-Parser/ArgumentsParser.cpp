#include "GArgs-Parser/ArgumentsParser.hpp"
#include "GArgs-Core/ArgumentsException.hpp"
#include "GArgs-Help/Argument.hpp"
#include <iostream>

int GetAmountOfValues(const std::string &argument_value);

namespace GArgs {
ArgumentsParser::ArgumentsParser(const std::string &program_title,
                                 const std::string &version,
                                 const bool &allow_relative_path)
    : m_name(program_title), m_version(version),
      m_allowRelative(allow_relative_path) {}

ArgumentsParser::~ArgumentsParser() {}

void ArgumentsParser::AddFlag(const FlagKey &flag) {
  m_structure.AddFlag(flag);
}

void ArgumentsParser::AddCommand(const CommandKey &command) {
  m_structure.AddCommand(command);
}

void ArgumentsParser::DisplayHelp() {
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
        if (arg->value != "") {
          arg->value += 9;
        }

        arg->value += argument;
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

      while (GetAmountOfValues(arg->value) < arg->valueAmount) {
        if (arg->value != "") {
          arg->value += 9;
        }

        arg->value += argument;

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
    (*this)[arg->name] = arg->value;
  }
}

bool ArgumentsParser::Contains(const std::string &key,
                               const std::string &value) {
  int pos;
  std::string readValue = (*this)[key];

  if (readValue.length() > 0) {
    pos = readValue.find(value);

    if (pos >= 0 && pos < readValue.length()) {
      return true;
    } else {
      return false;
    }
  } else {
    return false;
  }
}
} // namespace GArgs

int GetAmountOfValues(const std::string &argument_value) {
  int i = 0;
  int values = 0;

  while (i > 0) {
    i = argument_value.find(9, i);
    if (i > 0) {
      values++;
    }
  }

  return values;
}
