#include "ui_context.h"
#include "GLFW/glfw3.h"
#include "fonts/cousine_regular.cpp"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

namespace NRender {
bool UIContext::init(NWindow::IWindow *window) {
  IMGUI_CHECKVERSION();
  const char *glsl_version = "#version 130";
  ImGui::CreateContext();

  // Setup renderer backends
  ImGui_ImplGlfw_InitForOpenGL((GLFWwindow *)window->get_native_window(), true);
  ImGui_ImplOpenGL3_Init(glsl_version);

  ImGui::StyleColorsLight(&ImGui::GetStyle());

  set_content_scale();

  return true;
}

void UIContext::pre_render() {
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();

#ifdef _DEBUG
  bool show_demo_window = true;
  ImGui::ShowDemoWindow(&show_demo_window);
#endif
}

void UIContext::post_render() {
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void UIContext::shutdown() {
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
}

void UIContext::set_content_scale() {
  GLFWmonitor *primary = glfwGetPrimaryMonitor();

  glfwGetMonitorContentScale(primary, &content_scale_x, &content_scale_y);
  // Load custom fonts
  ImFont *font = ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(
      cousine_regular_compressed_data, cousine_regular_compressed_size,
      16 * content_scale_x / content_scale_y);
}
} // namespace NRender