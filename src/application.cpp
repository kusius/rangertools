#include "application.h"
#include "pch.h"

Application::Application(const std::string &name) {
  mWindow          = std::make_unique<NWindow::GLWindow>();
  mNetToolSystem   = std::make_unique<NSystem::NetToolSystem>();
  mApplicationData = std::make_unique<ApplicationData>();
  mWindow->init(1024, 720, name);
}

void Application::loop() {
  while (mWindow->is_running()) {
    mWindow->render(mApplicationData);
    mNetToolSystem->update(mApplicationData);
  }

  mNetToolSystem->shutdown();
}