cmake_minimum_required(VERSION 3.21)

find_package(fmt CONFIG REQUIRED)
find_package(Boost REQUIRED COMPONENTS lockfree)

set(CMAKE_CXX_STANDARD 20)

add_library(
  ${PROJECT_NAME} "dll_allocate.cpp" "detail/dll_object_pool_data.cpp"
                  "dll_object_pool.cpp" "dll_new.cpp")

if(BUILD_SHARED_LIBS AND WIN32)
  target_compile_definitions(
    ${PROJECT_NAME}
    PRIVATE "EXPORT_SPEC=__declspec(dllexport)"
    INTERFACE "EXPORT_SPEC=__declspec(dllimport)")
else()
  target_compile_definitions(${PROJECT_NAME} PUBLIC "EXPORT_SPEC=")
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt Boost::lockfree)

target_include_directories(
  ${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
                         $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

install(
  TARGETS ${PROJECT_NAME}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

install(FILES "dll_allocate.h" "dll_object_pool.h" "dll_allocator.hpp"
              "dll_object_pool.hpp"
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/ignosi)
