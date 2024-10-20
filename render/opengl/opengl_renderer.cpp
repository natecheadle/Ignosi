#include "opengl_renderer.h"

// clang-format off

#include <glad/glad.h>
#include <GLFW/glfw3.h>

// clang-format on

#include <window/window.h>

#include <memory>

#include "opengl/shader/opengl_shader.h"
#include "opengl/shader/opengl_shader_program.h"
#include "opengl/texture/opengl_texture.h"
#include "opengl_vertex_buffer.h"

namespace ignosi::render {
const system::Window& OpenGL_Renderer::AttachedWindow() const {
  return m_Window;
}

void OpenGL_Renderer::AttachWindow(system::Window window) {
  m_Window = std::move(window);

  // glad: load all OpenGL function pointers
  // ---------------------------------------
  if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) == 0) {
    throw std::runtime_error("Failed to initialize GLAD");
  }

  IgnosiWindowSize size = m_Window.GetActualSize();
  glViewport(0, 0, size.Width, size.Height);

  // configure global opengl state
  // -----------------------------
  // TODO this should be user configurable.
  glEnable(GL_DEPTH_TEST);
}

void OpenGL_Renderer::AttachedCamera(std::shared_ptr<Camera> camera) {
  m_pCamera = std::move(camera);
}

const std::shared_ptr<Camera>& OpenGL_Renderer::AttachedCamera() const {
  return m_pCamera;
}

std::unique_ptr<IVertexBuffer> OpenGL_Renderer::CreateBuffer(
    const VertexDataConfig& config, std::span<const float> vertexes) const {
  return std::make_unique<OpenGL_VertexBuffer>(config, vertexes);
}

std::unique_ptr<IVertexBuffer> OpenGL_Renderer::CreateBuffer(
    const VertexDataConfig& config, std::span<const float> vertexes,
    std::span<const std::uint32_t> indeces) const {
  return std::make_unique<OpenGL_VertexBuffer>(config, vertexes, indeces);
}

std::unique_ptr<IShader> OpenGL_Renderer::CreateShader(
    const std::filesystem::path& path,
    const std::vector<std::filesystem::path>& inc_paths) const {
  return OpenGL_Shader::Create(path, inc_paths);
}

std::unique_ptr<IShader> OpenGL_Renderer::CreateShader(
    const std::filesystem::path& path, ShaderType type,
    const std::vector<std::filesystem::path>& inc_paths) const {
  return OpenGL_Shader::Create(path, type, inc_paths);
}

std::unique_ptr<IShaderProgram> OpenGL_Renderer::CreateShaderProgram(
    const IShader* pFragmentShader, const IShader* pGeometryShader,
    const IShader* pVertexShader) const {
  return std::make_unique<OpenGL_ShaderProgram>(pFragmentShader,
                                                pGeometryShader, pVertexShader);
}

std::unique_ptr<ITexture> OpenGL_Renderer::CreateTexture(
    const std::filesystem::path& path, TextureUnit unit) const {
  return std::make_unique<OpenGL_Texture>(path, unit);
}

std::unique_ptr<ITexture> OpenGL_Renderer::CreateTexture(
    const ImageFile& image, TextureUnit unit) const {
  return std::make_unique<OpenGL_Texture>(image, unit);
}

void OpenGL_Renderer::ClearDepthBuffer() const { glClear(GL_DEPTH_BUFFER_BIT); }

void OpenGL_Renderer::ClearColorBuffer() const { glClear(GL_COLOR_BUFFER_BIT); }

void OpenGL_Renderer::SwapBuffers() {
  m_Window.SwapBuffers();
  m_Window.PollEvents();
}

void OpenGL_Renderer::Draw(const Mesh& mesh) const {
  // TODO - Material not yet supported
  // if (var.Material())
  // {
  //     var.Shader()->SetShaderVar("Material", *var.Material());
  // }
  mesh.Shader()->Use();
  mesh.Shader()->SetShaderVar("model", mesh.ModelMatrix());

  if (m_pCamera) {
    mesh.Shader()->SetShaderVar("view", m_pCamera->ViewPerspective());
    mesh.Shader()->SetShaderVar("viewPos", m_pCamera->CameraPosition());
    mesh.Shader()->SetShaderVar("projection", m_pCamera->Projection());
  }

  mesh.Vertexes()->Draw();
}
}  // namespace ignosi::render
