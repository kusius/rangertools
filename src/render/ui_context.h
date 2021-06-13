#pragma once

#include "render_base.h"

namespace NRender {
class UIContext : public RenderContext {
public:
  bool init(NWindow::IWindow *window) override;

  void pre_render() override;

  void post_render() override;

  void shutdown() override;
};
} // namespace NRender