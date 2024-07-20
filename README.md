# Blender Renderer

## Structure

To add a structure, use `void add_structure(const std::string &structure_str)` method to add the implied structure

---

`.add_structure("[group:property1=value,property2=value,property3=value]")`

## Properties

`type`:

default: flag

- cmd
- flag
- pos_arg

### Example

`.add_structure("[command:type=cmd]")`
