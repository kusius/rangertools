#pragma once
#include "window/window.h"

namespace NRender {
class RenderContext {
public:
  RenderContext() : mWindow(nullptr){};

  virtual bool init(NWindow::IWindow *window) {
    mWindow = window;
    return true;
  }

  virtual void pre_render() = 0;

  virtual void post_render() = 0;

  virtual void shutdown() = 0;

protected:
  NWindow::IWindow *mWindow;
};
} // namespace NRender