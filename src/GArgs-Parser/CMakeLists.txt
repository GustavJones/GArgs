cmake_minimum_required(VERSION 3.15)
project(GArgs-Parser)

file(GLOB SOURCES "*.cpp")
file(GLOB HEADERS "../../include/GArgs/*.hpp")
add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})
target_include_directories(${PROJECT_NAME} PRIVATE "../../include/")
target_link_libraries(${PROJECT_NAME} PRIVATE GArgs-Help GArgs-Core)
