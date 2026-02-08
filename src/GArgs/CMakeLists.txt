cmake_minimum_required(VERSION 3.15)
project(GArgs)

file(GLOB SOURCES "*.cpp")
add_library(GArgs ${SOURCES})
target_include_directories(GArgs PUBLIC "../../include/")
