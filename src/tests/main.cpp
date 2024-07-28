#include "GArgs-Core/ArgumentsException.hpp"
#include "GArgs-Help/CommandKey.hpp"
#include "GArgs-Help/FlagKey.hpp"
#include "GArgs-Parser/ArgumentsParser.hpp"
#include <iostream>

int main(int argc, char *argv[]) {
  GArgs::ArgumentsParser parser("Parser", "V1.0", true);
  try {
    parser.AddStructure("[flags:help=Flags,value_amount=0,argument_filter=--;"
                        "argument1:help=The First "
                        "Argument;argument2:help=The "
                        "Second Argument]");

    parser.AddFlag(GArgs::FlagKey("flags", "help", "Prints This message"));
    parser.AddCommand(GArgs::CommandKey("argument1", "run", "Runs a file"));

    parser.ParseArgs(argc, argv);

    std::cout << parser["flags"] << std::endl;

    if (parser.Contains("argument1", "help")) {
      parser.DisplayHelp();
    }
  } catch (const GArgs::ArgumentsException &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }
  return 0;
}
