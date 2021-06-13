#include "render_base.h"

#include <glad/glad.h>
#include <glfw/glfw3.h>

namespace NRender {
class OpenGLContext : public RenderContext {
public:
  bool init(NWindow::IWindow *window) override;

  void pre_render() override;

  void post_render() override;

  void shutdown() override;

private:
};
} // namespace NRender