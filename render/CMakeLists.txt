cmake_minimum_required(VERSION 3.21)

set(CMAKE_CXX_STANDARD 20)

project(ignosi-render)

find_package(OpenGL REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)

add_library(
  ${PROJECT_NAME}
  "detail/irenderer.cpp"
  "detail/opengl/opengl_renderer.cpp"
  "detail/opengl/opengl_vertex_buffer.cpp"
  "detail/opengl/shader/compute_opengl_shader.cpp"
  "detail/opengl/shader/fragment_opengl_shader.cpp"
  "detail/opengl/shader/geometry_opengl_shader.cpp"
  "detail/opengl/shader/opengl_shader.cpp"
  "detail/opengl/shader/opengl_shader_program.cpp"
  "detail/opengl/shader/vertex_opengl_shader.cpp"
  "detail/opengl/texture/opengl_texture.cpp"
  "detail/shader/preprocessor.cpp"
  "detail/shader/shader.cpp"
  "detail/texture/color.cpp"
  "detail/texture/color_rgb.cpp"
  "detail/texture/image_file.cpp"
  "detail/texture/material.cpp"
  "detail/texture/stb_implementation.cpp"
  "detail/texture/texture.cpp"
  "detail/camera/camera.cpp"
  "detail/camera/camera_2d.cpp"
  "detail/camera/camera_fly.cpp"
  "detail/objects/mesh.cpp")

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(${PROJECT_NAME}
                           PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/detail/)
target_include_directories(${PROJECT_NAME} PRIVATE ${OPENGL_INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt OpenGL::GL glad::glad)
target_link_libraries(${PROJECT_NAME} PUBLIC ignosi-math ignosi-system)
