cmake_minimum_required(VERSION 3.15)
project(GArgs)
enable_language(ASM_NASM)
string(REPLACE "<CMAKE_ASM_NASM_COMPILER>" "<CMAKE_C_COMPILER>" CMAKE_ASM_NASM_LINK_EXECUTABLE ${CMAKE_ASM_NASM_LINK_EXECUTABLE})

if(NOT CMAKE_BUILD_TYPE)
  message(STATUS "Set the build type to `Debug` as none was specified.")
  set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Choose the build type." FORCE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
option(BUILD_SHARED_LIBS "Building shared libraries" OFF)

include(GNUInstallDirs)
set(CMAKE_INSTALL_RPATH "$ORIGIN/${CMAKE_INSTALL_LIBDIR} ${CMAKE_INSTALL_FULL_LIBDIR}")
message(STATUS "Using default install RPATH of: ${CMAKE_INSTALL_RPATH}")

file(GLOB SUBMODULES "external/*")

foreach(SUBMODULE ${SUBMODULES})
  if(IS_DIRECTORY ${SUBMODULE})
    if(EXISTS "${SUBMODULE}/CMakeLists.txt")
      message(STATUS "Adding submodule: ${SUBMODULE}")
      add_subdirectory(${SUBMODULE})
    endif()
  endif()
endforeach()

include("src/sources.cmake")
