#pragma once

#include "render_base.h"

namespace NRender {
class UIContext : public RenderContext {
public:
  bool init(NWindow::IWindow *window) override;

  void pre_render() override;

  void post_render() override;

  void shutdown() override;

  void set_content_scale();

private:
  float content_scale_x;
  float content_scale_y;
};
} // namespace NRender