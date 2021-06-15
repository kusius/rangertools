#pragma once

#include "imgui/imgui.h"
#include "menu_item.h"
#include "pch.h"
#include "utilities/application_data.h"

using namespace NAppData;

namespace NUI {

class MainMenuBar {
public:
  MainMenuBar();
  void render();
  void add_menu_item(std::shared_ptr<IMenuItem> menu_item);

private:
  std::vector<std::shared_ptr<IMenuItem>> mMenuItems;
  bool mShowMetrics;
  bool mShowStyling;
  bool mShowAbout;
};

} // namespace NUI