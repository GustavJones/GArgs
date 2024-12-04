#include "GArgs-Help/Structure.hpp"
#include "GArgs-Core/ArgumentsException.hpp"
#include <cctype>
#include <string>

namespace GArgs {
Structure::Structure() {}
Structure::~Structure() {
  for (auto &item : *this) {
    delete item;
  }
}

void Structure::Parse(const std::string &structure_str) {
  int parseStartIndex = 0;
  int parseEndIndex = 0;
  int iterator = 0;
  std::string argument;
  std::string argumentName;
  std::vector<std::pair<std::string, std::string>> argumentProperties;
  parseStartIndex = structure_str.find("[");
  parseEndIndex = structure_str.find("]");

  // Check for improper string
  if (parseStartIndex == -1 || parseEndIndex == -1) {
    throw ArgumentsException("Cannot Find Structure Start or End");
  }

  iterator = parseStartIndex + 1;
  while (iterator <= parseEndIndex) {
    if (structure_str[iterator] == ';' || iterator == parseEndIndex) {
      _ParseStructureArgument(argument, argumentName, argumentProperties);

      _AddArgumentToStructure(argumentName, argumentProperties);

      argument = "";
      iterator++;
    }

    argument += structure_str[iterator];
    iterator++;
  }
}

std::string Structure::HelpMessage(const std::string &title,
                                   const std::string &version) const {
  std::string output;

  output += title + ' ' + version + '\n';

  output += title + ' ';

  // Display Argument Structure
  for (const auto &argument : *this) {
    output += '[' + argument->name + ']' + ' ';
  }

  output += '\n';
  output += '\n';

  output += "Structure: \n";

  // Display Argument Structure Help
  for (const auto &argument : *this) {
    output += argument->name + ": " + argument->help + '\n';
  }

  output += '\n';
  output += '\n';

  for (const auto &argument : *this) {
    output += argument->name + ": \n";
    for (const auto &key : m_keys) {
      if (key.parent == argument->name) {
        output += key.key + " : " + key.help + '\n';
      }
    }
    output += '\n';
  }

  return output;
}

void Structure::AddKey(const Key &key) { m_keys.push_back(key); }

/// Parse Argument Structure line from structure string
void Structure::_ParseStructureArgument(
    const std::string &argument_str, std::string &argument_name,
    std::vector<std::pair<std::string, std::string>> &argument_properties) {
  int colonIndex = argument_str.find(':');
  std::string property;
  std::string propertyName;
  std::string propertyValue;

  argument_name = "";
  argument_properties.clear();

  // Parse Argument Name
  if (colonIndex < 0) {
    throw GArgs::ArgumentsException("Argument Name end not found");
  } else {
    for (int i = 0; i < colonIndex; i++) {
      argument_name += argument_str[i];
    }
  }

  // Parse Properties and Store in argument_properties
  for (int j = colonIndex + 1; j <= argument_str.length(); j++) {
    if (argument_str[j] == ',' || j == argument_str.length()) {
      _ParseStructureProperty(property, propertyName, propertyValue);
      argument_properties.emplace_back(propertyName, propertyValue);
      property = "";
    } else {
      property += argument_str[j];
    }
  }
}

/// Parse property line in argument line
void Structure::_ParseStructureProperty(const std::string &property_str,
                                        std::string &property_name,
                                        std::string &property_value) {
  int equalIndex = property_str.find('=');

  property_name = "";
  property_value = "";

  if (equalIndex < 0) {
    throw GArgs::ArgumentsException("Property Doesn't have a value");
  } else {
    for (int i = 0; i < equalIndex; i++) {
      property_name += property_str[i];
    }
  }

  for (int j = equalIndex + 1; j < property_str.length(); j++) {
    property_value += property_str[j];
  }
}

void Structure::_AddArgumentToStructure(
    const std::string &argument_name,
    const std::vector<std::pair<std::string, std::string>>
        &argument_properties) {

  bool required = true;
  std::string help;
  std::string argumentFilter;
  unsigned int valueAmount = 1;

  GArgs::Argument *argument = new GArgs::Argument;

  for (const auto &property : argument_properties) {
    if (property.first == "help") {
      help = property.second;
    } else if (property.first == "required") {
      std::string requiredStr;
      for (char c : property.second) {
        requiredStr += tolower(c);
      }

      if (requiredStr == "false") {
        required = false;
      } else {
        required = true;
      }
    } else if (property.first == "argument_filter") {
      argumentFilter = property.second;
    } else if (property.first == "value_amount") {
      valueAmount = std::stoi(property.second);
    }
  }

  argument->name = argument_name;
  argument->help = help;
  argument->required = required;
  argument->argumentFilter = argumentFilter;
  argument->valueAmount = valueAmount;

  this->push_back(argument);
}
} // namespace GArgs
