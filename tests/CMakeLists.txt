cmake_minimum_required(VERSION 3.15)

project(${CMAKE_PROJECT_NAME}_TESTS 
VERSION 1.0.0
LANGUAGES C CXX)

find_package(fmt CONFIG REQUIRED)
find_package(Catch2 CONFIG REQUIRED)

add_subdirectory("utility")
