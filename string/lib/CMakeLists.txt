cmake_minimum_required(VERSION 3.21)

set(CMAKE_CXX_STANDARD 20)

add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(${PROJECT_NAME}
                           INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

install(FILES "string_literal.h"
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/ignosi/units)
