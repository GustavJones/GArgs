#include "GArgs/Parser.hpp"
#include "GArgs/Version.hpp"
#include <iostream>

int main(int argc, char *argv[]) {
  // Create a parser object
  GArgs::Parser parser("Program Name", GArgs::Version<size_t>{1, 0, 0});

  // Create an argument slot
  // Contructor takes: slot name, decription, filter, required amount, max amount (0 for infinite)
  GArgs::ArgumentSlot slot("flags", "Slot decription", "--", 0, 0);

  // Add a key to display in help message
  slot.AddKey(GArgs::ArgumentKey("--help"));

  parser.AddSlot(slot);

  parser.Parse(argc, argv);

  // Check if argument value is contained in a slot
  if (parser["flags"].Has("--help")) {
    std::cout << parser.Help() << std::endl;
    return 0;
  }

  // Print arguments in flag slot
  for (size_t __valuesIndex = 0; __valuesIndex < parser["flags"].Size(); __valuesIndex++) {
    std::cout << parser["flags"][__valuesIndex] << std::endl;
  }

  return 0;
}
