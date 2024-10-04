cmake_minimum_required(VERSION 3.21)

project(ignosi-system)

find_package(glfw3 CONFIG REQUIRED)

set(CMAKE_CXX_STANDARD 20)

add_library(${PROJECT_NAME} SHARED "window/window.cpp"
                                   "window/detail/glfw_window.cpp")

if(BUILD_SHARED_LIBS AND WIN32)
  target_compile_definitions(
    ${PROJECT_NAME}
    PRIVATE "SYSTEM_EXPORT_SPEC=__declspec(dllexport)"
    INTERFACE "SYSTEM_EXPORT_SPEC=__declspec(dllimport)")
else()
  target_compile_definitions(${PROJECT_NAME} PUBLIC "SYSTEM_EXPORT_SPEC=")
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE glfw)

target_include_directories(
  ${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)

install(
  TARGETS ${PROJECT_NAME}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

install(FILES "window/window.h"
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/ignosi/system)
