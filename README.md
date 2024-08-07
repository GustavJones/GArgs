# GArgs

## How To Use:

1. Define a structure
2. Add flag options and commands
3. Get values of arguments

## Structure

To add a structure, use `void add_structure(const std::string &structure_str)` method to add the implied structure

---

## Template

`.add_structure("[argument_name1:property1=value,property2=value,property3=value;argument_name2:property1=value,property2=value]")`

## Properties

`help`:

The help string for argument position

default: ""

- Any String

`value_amount`:

Amount of arguments for the group

- unsigned integer
- default=1
- for infinate arguments use 0 (must also set argument_filter)

`argument_filter`:

Set the filter of what characters the argument value must begin with

- String
- Default=Unset
- Set "--" for flag filter

`required`:
NOT IMPLEMENTED
Sets the priority of the argument

- Bool
- Default=true

## Usage

```cpp
    #include "GArgs.hpp"

    GArgs::Parser parser("ApplicationName", "V1.0"); // ArgumentParser can also be used
    parser.AddStructure("[argument1:help=Arg 1;argument2:help=Arg 2]");

    parser.AddKey(GArgs::Key("argument1", "help", "Prints This message"));
    parser.AddKey(GArgs::Key("argument2", "*", "Runs a file"));

    parser.ParseArgs(argc, argv);

    std::cout << parser["argument2"] << std::endl;

    if (parser.Contains("argument1", "help")) {
      parser.DisplayHelp();
    }

```
