cmake_minimum_required(VERSION 3.21)

set(CMAKE_CXX_STANDARD 20)

project(ignosi-render)

find_package(OpenGL REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)

add_library(
  ${PROJECT_NAME}
  "irenderer.cpp"
  "opengl/opengl_renderer.cpp"
  "opengl/opengl_vertex_buffer.cpp"
  "opengl/shader/compute_opengl_shader.cpp"
  "opengl/shader/fragment_opengl_shader.cpp"
  "opengl/shader/geometry_opengl_shader.cpp"
  "opengl/shader/opengl_shader.cpp"
  "opengl/shader/opengl_shader_program.cpp"
  "opengl/shader/vertex_opengl_shader.cpp"
  "opengl/texture/opengl_texture.cpp"
  "shader/preprocessor.cpp"
  "shader/shader.cpp"
  "texture/color.cpp"
  "texture/color_rgb.cpp"
  "texture/image_file.cpp"
  "texture/material.cpp"
  "texture/stb_implementation.cpp"
  "texture/texture.cpp"
  "camera/camera.cpp"
  "camera/camera_2d.cpp"
  "camera/camera_fly.cpp"
  "objects/mesh.cpp")

if(BUILD_SHARED_LIBS AND WIN32)
  target_compile_definitions(
    ${PROJECT_NAME}
    PRIVATE "RENDER_EXPORT_SPEC=__declspec(dllexport)"
    INTERFACE "RENDER_EXPORT_SPEC=__declspec(dllimport)")
else()
  target_compile_definitions(${PROJECT_NAME} PUBLIC "RENDER_EXPORT_SPEC=")
endif()

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${OPENGL_INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt OpenGL::GL glad::glad)
target_link_libraries(${PROJECT_NAME} PUBLIC ignosi-math ignosi-system)
