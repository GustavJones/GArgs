#include "GArgs/ArgumentsParser.hpp"
#include "GArgs/Argument.hpp"
#include "GArgs/ArgumentsException.hpp"
#include <iostream>
#include <utility>

namespace GArgs {
ArgumentsParser::ArgumentsParser(const std::string &program_title,
                                 const std::string &version,
                                 const bool &allow_relative_path)
    : m_name(program_title), m_version(version),
      m_allowRelative(allow_relative_path) {}

ArgumentsParser::~ArgumentsParser() {}

void ArgumentsParser::AddFlag(const FlagKey &flag) { m_flags.push_back(flag); }

void ArgumentsParser::AddCommand(const CommandKey &command) {
  m_commands.push_back(command);
}

void ArgumentsParser::DisplayHelp() {
  std::string output;

  output += m_name + ' ' + m_version + '\n';

  // Display Argument Structure
  output += m_name + " [flags] ";
  for (const auto &argument : m_structure) {
    switch (argument->type) {
    case GArgs::ArgumentTypes::Command:
      output += '[' + argument->name + ']' + ' ';
      break;
    case GArgs::ArgumentTypes::PositionalArg:
      output += '(' + argument->name + ')' + ' ';
      break;
    }
  }

  output += '\n';

  // Display Flags help
  output += "flags: \n";
  for (const auto &flag : m_flags) {
    output += flag.flag + ": " + flag.help + '\n';
  }

  output += '\n';

  // Display Argument Structure Help
  for (const auto &argument : m_structure) {
    output += argument->name + ": " + argument->help + '\n';
  }

  output += '\n';

  for (const auto &argument : m_structure) {
    if (argument->type == GArgs::ArgumentTypes::Command) {
      output += argument->name + ": \n";
      for (const auto &argumentKey : m_commands) {
        if (argumentKey.parent == argument->name) {
          output += argumentKey.cmd + ": " + argumentKey.help + '\n';
        }
      }
    }
  }

  std::cout << output << std::endl;
}

Structure &ArgumentsParser::AddStructure(const std::string &structure_str) {
  m_structure.Parse(structure_str);
  _UpdateParserMap();
  return m_structure;
}

Structure &ArgumentsParser::ClearStructure() {
  for (auto &item : m_structure) {
    delete item;
  }
  m_structure.clear();
  _UpdateParserMap();
  return m_structure;
}

void ArgumentsParser::ParseArgs(int argc, char *argv[]) {
  // TODO
  std::string argument;

  for (int i = 0; i < argc; i++) {
    argument = argv[i];

    // Relative Path Running Check
    if (i == 0) {
      if (argument != m_name && !m_allowRelative) {
        throw GArgs::ArgumentsException("Program run from relative path");
      }
      continue;
    }

    // Flag
    if (argument.find("-") == 0 &&
        (!(argument[1] > '0' && argument[1] < '9') || argument[1] == '-')) {
      m_activeFlags.push_back(argument);
      continue;
    }

    for (auto &arg : m_structure) {
      if (arg->value != "") {
        continue;
      } else {
        arg->value = argument;
        break;
      }
    }
  }

  _UpdateParserMap();
}

void ArgumentsParser::_UpdateParserMap() {
  this->clear();
  for (const auto &arg : m_structure) {
    (*this)[arg->name] = arg->value;
  }

  for (const auto &flag : m_activeFlags) {
    (*this)[flag] = "active";
  }
}
} // namespace GArgs
