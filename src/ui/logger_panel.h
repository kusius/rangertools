#pragma once
#include "imgui/imgui.h"
#include "menu_item.h"
#include "systems/logger.h"
#include <memory>
#include <vector>

namespace NUI {
class LoggerPanel : public IMenuItem {
public:
  LoggerPanel();
  void render();

private:
  void clear();

  bool auto_scroll;
  ImGuiTextFilter filter;
  float height = 1200.0f;
};
} // namespace NUI