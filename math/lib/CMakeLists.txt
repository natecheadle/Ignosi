cmake_minimum_required(VERSION 3.21)

set(CMAKE_CXX_STANDARD 20)

add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(${PROJECT_NAME}
                           INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} INTERFACE ignosi-units)

install(FILES "vector.hpp" "float_compare.hpp" "square_matrix.hpp"
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/ignosi/container)
