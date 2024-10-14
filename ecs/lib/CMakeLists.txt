cmake_minimum_required(VERSION 3.21)

set(CMAKE_CXX_STANDARD 20)

add_library(${PROJECT_NAME} STATIC "entity.cpp" "query.cpp" "world.cpp")

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(${PROJECT_NAME} PUBLIC ignosi-memory)

install(
  TARGETS ${PROJECT_NAME}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

install(
  FILES "component.h"
        "ecs_pointer.h"
        "entity.h"
        "query.h"
        "system.h"
        "type_id.h"
        "world.h"
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/ignosi/ecs)
