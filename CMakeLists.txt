cmake_minimum_required(VERSION 3.15)
project(GArgs)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

add_library(GArgs INTERFACE)
target_link_libraries(GArgs INTERFACE GArgs-Core GArgs-Help GArgs-Parser)

add_subdirectory("src/GArgs-Parser")
add_subdirectory("src/GArgs-Help")
add_subdirectory("src/GArgs-Core")
# add_subdirectory("src/tests")
