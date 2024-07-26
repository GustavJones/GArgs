#include "GArgs/ArgumentsException.hpp"
#include "GArgs/ArgumentsParser.hpp"
#include "GArgs/CommandKey.hpp"
#include "GArgs/FlagKey.hpp"
#include <iostream>

int main(int argc, char *argv[]) {
  GArgs::ArgumentsParser parser("Parser", "V1.0", true);
  try {
    parser.AddStructure(
        "[argument1:type=cmd,help=The First "
        "Argument;argument2:type=pos_arg,help=The Second Argument]");

    parser.AddFlag(GArgs::FlagKey("help", "Prints This message"));
    parser.AddCommand(GArgs::CommandKey("argument1", "run", "Runs a file"));

    parser.ParseArgs(argc, argv);

    if (parser["--help"] != "") {
      parser.DisplayHelp();
    }
  } catch (const GArgs::ArgumentsException &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }
  return 0;
}
