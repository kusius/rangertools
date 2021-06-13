#include "gl_window.h"

namespace NWindow {
bool GLWindow::init(int width, int height, const std::string &title) {
  this->width  = width;
  this->height = height;
  this->title  = title;

  mRenderContext->init(this);
  mUIContext->init(this);

  return mIsRunning;
}

GLWindow::~GLWindow() {
  mUIContext->shutdown();
  mRenderContext->shutdown();
}

void GLWindow::render(std::unique_ptr<ApplicationData> &application_data) {
  mRenderContext->pre_render();
  mUIContext->pre_render();

  mNetToolPanel->render(application_data);

  mUIContext->post_render();
  mRenderContext->post_render();
}

void GLWindow::on_close() { mIsRunning = false; }

void GLWindow::on_resize(int width, int height) {}
} // namespace NWindow