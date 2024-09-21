cmake_minimum_required(VERSION 3.21)

project(ignosi)

enable_language(CXX)

include(GNUInstallDirs)

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

add_subdirectory("memory")
