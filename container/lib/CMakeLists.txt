cmake_minimum_required(VERSION 3.21)

set(CMAKE_CXX_STANDARD 20)

add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(
  ${PROJECT_NAME} INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)

target_link_libraries(${PROJECT_NAME} INTERFACE ignosi-memory)

install(FILES "ring_buffer.hpp"
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/ignosi/container)
