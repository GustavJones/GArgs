#include "GArgs/Parser.hpp"
#include <stdexcept>
#include <string>

namespace GArgs {
const ArgumentValuesContainer & Parser::operator[](const std::string &_slot) const {
  for (size_t __slotIndex = 0; __slotIndex < m_slots.size(); __slotIndex++) {
    const auto &slot = m_slots[__slotIndex];
    if (slot.GetName() == _slot) {
      return slot.GetValues();
    }
  }

  throw std::runtime_error("Slot not in parser.");
}

ArgumentValuesContainer &Parser::operator[](const std::string &_slot) {
  for (size_t __slotIndex = 0; __slotIndex < m_slots.size(); __slotIndex++) {
    auto &slot = m_slots[__slotIndex];
    if (slot.GetName() == _slot) {
      return slot.GetValues();
    }
  }

  throw std::runtime_error("Slot not in parser.");
}

void Parser::AddSlot(const ArgumentSlot &_slot) { m_slots.push_back(_slot); }

std::string Parser::Help() {
  std::string out;
  out += m_applicationName + " - " + (std::string)m_version + "\n";

  out += "Usage: " + m_applicationName + " ";

  for (size_t __slotIndex = 0; __slotIndex < m_slots.size(); __slotIndex++) {
    const auto &slot = m_slots[__slotIndex];

    out += "[" + slot.GetName() + "] ";
  }

  out += "\n\n";

  for (size_t __slotIndex = 0; __slotIndex < m_slots.size(); __slotIndex++) {
    const auto &slot = m_slots[__slotIndex];
    out += slot.GetName() + ": " + slot.GetDescription() + " | ['" + slot.GetFilter() + "'] | ";

    if (slot.GetMaxAmount() == 0) {
      out += "Max: infinity | ";
    } else {
      out += "Max: " + std::to_string(slot.GetMaxAmount()) + " | ";
    }
    out +=
        "Required: " + std::to_string(slot.GetRequiredAmount()) + "\n";
    out += "Keys: \n";

    for (size_t __argIndex = 0; __argIndex < slot.GetArguments().Size(); __argIndex++) {
      const auto arg = slot.GetArguments()[__argIndex];
      out += "   " + (std::string)arg + "\n";
    }

    out += "\n";
  }

  return out;
}

void Parser::Parse(int _argc, char *_argv[]) {
  size_t argIndex = 1;

  for (size_t __slotIndex = 0; __slotIndex < m_slots.size(); __slotIndex++) {
    size_t capacity = 0;
    auto &slot = m_slots[__slotIndex];

    bool infiniteArgs = false;
    if (slot.GetMaxAmount() == 0) {
      infiniteArgs = true;
    }

    while ((capacity < slot.GetMaxAmount() || infiniteArgs) && argIndex < _argc) {
      const std::string arg = _argv[argIndex];

      if (capacity >= slot.GetMaxAmount() && !infiniteArgs) {
        capacity = 0;
        break;
      }

      if (arg.length() < slot.GetFilter().length()) {
        capacity = 0;
        break;
      }

      bool match = true;
      for (size_t __filterIndex = 0; __filterIndex < slot.GetFilter().length(); __filterIndex++) {
        if (arg[__filterIndex] != slot.GetFilter()[__filterIndex]) {
          match = false;
          break;
        }
      }

      if (!match) {
        capacity = 0;
        break;
      }

      ArgumentValue value(arg);
      slot.AddValue(value);
      capacity++;
      argIndex++;
    }
  }

  for (size_t __slotIndex = 0; __slotIndex < m_slots.size(); __slotIndex++) {
    if (!m_slots[__slotIndex].HasRequired()) {
      throw std::runtime_error("Argument slot doesn't have required amount of values.");
    }
  }
}
} // namespace GArgs
