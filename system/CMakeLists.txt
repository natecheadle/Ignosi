cmake_minimum_required(VERSION 3.21)

project(${PROJECT_NAME}-system)

find_package(glfw3 CONFIG REQUIRED)

set(CMAKE_CXX_STANDARD 20)

add_library(${PROJECT_NAME} SHARED "window/window.cpp"
                                   "window/detail/glfw_window.cpp")

target_link_libraries(${PROJECT_NAME} PUBLIC ignosi-dll)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

install(
  TARGETS ${PROJECT_NAME}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

install(FILES "window/window.h"
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/ignosi/system)
