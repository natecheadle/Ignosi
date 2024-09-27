cmake_minimum_required(VERSION 3.21)

project(ignosi-memory)

enable_language(CXX)

add_subdirectory("lib")

if(BUILD_TESTS)
  add_subdirectory("test")
endif()
