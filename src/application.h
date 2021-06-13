#include "systems/nettool_system.h"
#include "utilities/application_data.h"
#include "window/gl_window.h"
#include <string>

class Application {
public:
  Application(const std::string &name);

  static Application &Instance() { return *instance; }

  void loop();

private:
  static Application *instance;

  std::unique_ptr<ApplicationData> mApplicationData;

  std::unique_ptr<NWindow::GLWindow> mWindow;

  std::unique_ptr<NSystem::NetToolSystem> mNetToolSystem;
};