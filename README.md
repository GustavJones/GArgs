# Blender Renderer

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

`type`:

The type of argument added

default: pos_arg

- cmd
- pos_arg

`help`:

The help string for argument position

default: ""

- Any String

### Examples

`.add_structure("[ProgramFunction:type=cmd]")`
