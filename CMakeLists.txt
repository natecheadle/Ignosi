cmake_minimum_required(VERSION 3.21)

project(ignosi)

enable_language(CXX)

include(GNUInstallDirs)

if(MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /utf-8")
endif()

if(${BUILD_COVERAGE})
  set(CLANG_COVERAGE_COMPILE_FLAGS
      "-fprofile-instr-generate -fcoverage-mapping")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CLANG_COVERAGE_COMPILE_FLAGS}")
endif()

if(NOT DEFINED BUILD_TESTS)
  set(BUILD_TESTS TRUE)
endif()

execute_process(
  COMMAND
    ${CMAKE_COMMAND} -E create_symlink
    ${CMAKE_BINARY_DIR}/compile_commands.json
    ${CMAKE_SOURCE_DIR}/compile_commands.json)

add_compile_definitions(PUBLIC $<$<CONFIG:Debug>:DEBUG>)

add_subdirectory("container")
add_subdirectory("ecs")
add_subdirectory("math")
add_subdirectory("memory")
add_subdirectory("string")
add_subdirectory("units")
