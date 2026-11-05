# Set the minimum version of CMake required
cmake_minimum_required(VERSION 3.23)

# Define the project
project(
  JoeGameEngine
  VERSION 1.0
  DESCRIPTION "My first SDL3 Game"
  LANGUAGES CXX
)

# Set the C++ standard to C++20
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(
  CMAKE_RUNTIME_OUTPUT_DIRECTORY
  "${CMAKE_BINARY_DIR}/$<CONFIGURATION>"
)

set(
  CMAKE_LIBRARY_OUTPUT_DIRECTORY
  "${CMAKE_BINARY_DIR}/$<CONFIGURATION>"
)

add_executable(JoeGameEngine
  src/main.cpp
  src/GameObject.cpp
  src/GameObject.hpp
)

if(APPLE)
  set_target_properties(JoeGameEngine PROPERTIES
    INSTALL_RPATH "@executable_path;@loader_path"
    BUILD_WITH_INSTALL_RPATH TRUE
    MACOSX_RPATH TRUE
  )
elseif(UNIX)
  set_target_properties(JoeGameEngine PROPERTIES
    INSTALL_RPATH "$ORIGIN"
    BUILD_WITH_INSTALL_RPATH TRUE
  )
endif()

# Specify that we want to build SDL_TTF's dependencies
set(SDLTTF_VENDORED ON) 

# Set a variable for our vendor directory
set(VENDOR_DIR "${PROJECT_SOURCE_DIR}/vendor") 

# Add the SDL libraries from our submodules
add_subdirectory(${VENDOR_DIR}/SDL) 
add_subdirectory(${VENDOR_DIR}/SDL_image) 
add_subdirectory(${VENDOR_DIR}/SDL_ttf)

target_link_libraries(JoeGameEngine 
  SDL3::SDL3 
  SDL3_image::SDL3_image 
  SDL3_ttf::SDL3_ttf 
)