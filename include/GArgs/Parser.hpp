#pragma once
#include "GArgs/Argument.hpp"
#include "GArgs/Version.hpp"
#include <cstddef>
#include <string>
#include <vector>

namespace GArgs {
class Parser {
private:
  std::string m_applicationName;
  Version<size_t> m_version;

  std::vector<ArgumentSlot> m_slots;

public:
  Parser(const std::string &_name, const Version<size_t> &_version)
      : m_applicationName(_name), m_version(_version) {};
  Parser(Parser &&) = default;
  Parser(const Parser &) = default;
  Parser &operator=(Parser &&) = default;
  Parser &operator=(const Parser &) = default;
  ~Parser() = default;

  [[nodiscard]]
  const ArgumentValuesContainer &operator[](const std::string &_slot) const;

  [[nodiscard]]
  ArgumentValuesContainer &operator[](const std::string &_slot);
  void AddSlot(const ArgumentSlot &_slot);

  std::string Help();
  void Parse(int _argc, char *_argv[]);
};
} // namespace GArgs
