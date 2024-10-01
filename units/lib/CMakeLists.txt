cmake_minimum_required(VERSION 3.21)

set(CMAKE_CXX_STANDARD 20)

find_package(gcem CONFIG REQUIRED)

add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(
  ${PROJECT_NAME} INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)

target_link_libraries(${PROJECT_NAME} INTERFACE gcem ignosi-string ignosi-math)

install(
  FILES "radian.hpp"
        "degree.hpp"
        "angle.hpp"
        "angular_acceleration.hpp"
        "angular_velocity.hpp"
        "minute.hpp"
        "second.hpp"
        "time.hpp"
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/ignosi/units)
