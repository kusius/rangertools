#include "render/opengl_context.h"
#include "render/ui_context.h"
#include "ui/main_menu_bar.h"
#include "ui/nettool_panel.h"
#include "window.h"
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <memory>

using namespace NRender;
using namespace NUI;

namespace NWindow {
class GLWindow : public IWindow {
public:
  GLWindow() : mIsRunning(true), mWindow(nullptr) {
    mRenderContext = std::make_unique<OpenGLContext>();
    mUIContext     = std::make_unique<UIContext>();
    mNetToolPanel  = std::make_shared<NetToolPanel>();
    mMainMenuBar   = std::make_unique<MainMenuBar>();

    mMainMenuBar->add_menu_item(mNetToolPanel);
  }

  ~GLWindow();

  bool init(int width, int height, const std::string &title);

  void *get_native_window() override { return mWindow; }

  void set_native_window(void *window) { mWindow = (GLFWwindow *)window; }

  bool is_running() { return mIsRunning; }

  void on_close() override;

  void on_resize(int width, int height) override;

  void render(std::unique_ptr<ApplicationData> &application_data);

private:
  GLFWwindow *mWindow;

  std::shared_ptr<NetToolPanel> mNetToolPanel;

  std::unique_ptr<MainMenuBar> mMainMenuBar;

  std::unique_ptr<UIContext> mUIContext;

  std::unique_ptr<OpenGLContext> mRenderContext;

  bool mIsRunning;
};
} // namespace NWindow
