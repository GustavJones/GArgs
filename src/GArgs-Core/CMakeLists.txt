cmake_minimum_required(VERSION 3.5)
project(GArgs-Core)

file(GLOB SOURCES "*.cpp")
file(GLOB HEADERS "../../include/GArgs/*.hpp")
add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})
target_include_directories(${PROJECT_NAME} PRIVATE "../../include/")
