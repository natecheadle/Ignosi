cmake_minimum_required(VERSION 3.21)

find_package(fmt CONFIG REQUIRED)
find_package(Boost REQUIRED COMPONENTS lockfree)

set(CMAKE_CXX_STANDARD 20)

add_library(${PROJECT_NAME} "allocate.cpp" "detail/object_pool_impl.cpp"
                            "object_pool.cpp" "new.cpp")

if(BUILD_SHARED_LIBS AND WIN32)
  target_compile_definitions(
    ${PROJECT_NAME}
    PRIVATE "MEMORY_EXPORT_SPEC=__declspec(dllexport)"
    INTERFACE "MEMORY_EXPORT_SPEC=__declspec(dllimport)")
else()
  target_compile_definitions(${PROJECT_NAME} PUBLIC "MEMORY_EXPORT_SPEC=")
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt-header-only
                                              Boost::lockfree)

target_include_directories(
  ${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)

install(
  TARGETS ${PROJECT_NAME}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

install(FILES "i_object_pool.h" "allocate.h" "object_pool.h" "allocator.hpp"
              "object_pool.hpp"
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/ignosi/memory)
