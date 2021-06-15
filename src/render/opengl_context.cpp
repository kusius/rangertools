#include "opengl_context.h"

#include <stdio.h>

namespace NRender {

static void glfw_error_callback(int error, const char *description) {
  fprintf(stderr, "[Error] OpenGLContext %d: %s\n", error, description);
}

static void on_window_close_callback(GLFWwindow *window) {
  NWindow::IWindow *pWindow =
      static_cast<NWindow::IWindow *>(glfwGetWindowUserPointer(window));
  pWindow->on_close();
}

static void on_window_resize_callback(GLFWwindow *window, int width,
                                      int height) {
  NWindow::IWindow *pWindow =
      static_cast<NWindow::IWindow *>(glfwGetWindowUserPointer(window));
  pWindow->on_resize(width, height);
}

bool OpenGLContext::init(NWindow::IWindow *window) {
  __super::init(window);

  // Init GLFW/OpenGL
  if (!glfwInit())
    return false;

  auto glWindow = glfwCreateWindow(window->Width, window->Height,
                                   window->title.c_str(), nullptr, nullptr);
  window->set_native_window(glWindow);

  if (!glWindow) {
    return false;
  }

  // associate our IWindow as the manager of the native GLFWWindow
  // in order to delegate callbacks to our implementation via
  // glfwGetWindowUserPointer(void* window)
  glfwSetWindowUserPointer(glWindow, window);

  glfwSetErrorCallback(glfw_error_callback);
  glfwSetWindowCloseCallback(glWindow, on_window_close_callback);
  glfwSetWindowSizeCallback(glWindow, on_window_resize_callback);
  glfwMakeContextCurrent(glWindow);
  glfwSwapInterval(1); // vsync

  // Init GLAD GL bindings
  bool err = gladLoadGL() == 0;
  if (err) {
    fprintf(stderr, "Failed to init OpenGL loader\n");
    return false;
  }

  return true;
}

void OpenGLContext::pre_render() {
  glViewport(0, 0, mWindow->Width, mWindow->Height);
  glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
  glClear(GL_COLOR_BUFFER_BIT);
}

void OpenGLContext::post_render() {
  glfwPollEvents();
  glfwSwapBuffers((GLFWwindow *)mWindow->get_native_window());
}

void OpenGLContext::shutdown() {
  glfwDestroyWindow((GLFWwindow *)mWindow->get_native_window());
  glfwTerminate();
}
} // namespace NRender