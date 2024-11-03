#include "GArgs/GArgs.hpp"
#include <iostream>

int main(int argc, char *argv[]) {
  GArgs::Parser parser("Parser", "V1.0", true);
  try {
    parser.AddStructure("[flags:help=Flags,value_amount=0,argument_filter=--;"
                        "argument1:help=The First "
                        "Argument;argument2:help=The "
                        "Second Argument]");

    parser.AddKey(GArgs::Key("flags", "help", "Prints This message"));
    parser.AddKey(GArgs::Key("argument1", "run", "Runs a file"));

    parser.ParseArgs(argc, argv);

    for (const auto &flag : parser["flags"]) {
      std::cout << flag << std::endl;
    }

    if (parser.Contains("argument1", "help")) {
      parser.DisplayHelp();
    }
  } catch (const GArgs::ArgumentsException &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }
  return 0;
}
