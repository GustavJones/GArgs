# GArgs

## Table of content
1. [Description](#description)
2. [Installation](#installation)
3. [Usage](#usage)

## Description

This is a simple C++ library to add a low level of command line argument parsing.
It seperates arguments into slots with filters and amounts.

## Installation

Clone this repo to your project or setup a git submodule.
Include this project to your cmake config with `add_subdirectory`.
Link the library to your project with the name `GArgs`.
[Example](src/tests/CMakeLists.txt)

## Usage

```c++
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

```
