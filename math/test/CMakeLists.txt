cmake_minimum_required(VERSION 3.21)

project(${PROJECT_NAME}-test)

include(GoogleTest)
include(CopyDlls)

set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME} "main.cpp" "vector_tests.cpp" "matrix_tests.cpp")

find_package(GTest CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE GTest::gtest ignosi-math glm::glm)

copy_dlls(${PROJECT_NAME})
gtest_add_tests(TARGET ${PROJECT_NAME})

install(
  TARGETS ${PROJECT_NAME}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
