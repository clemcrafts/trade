# Specify the minimum version of CMake required to build this project
cmake_minimum_required(VERSION 3.10)

# Define the project name and the languages used
project(trade LANGUAGES CXX)

# Set C++ Standard
set(CMAKE_CXX_STANDARD 17)

# Find OpenSSL package
find_package(OpenSSL REQUIRED)

# Include external projects (like CPR)
add_subdirectory(external)

# Include the src directory
add_subdirectory(src)

# Ensure the include directories for OpenSSL are available to the project
include_directories(${OPENSSL_INCLUDE_DIR})