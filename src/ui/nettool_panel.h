#pragma once

#include "imgui/imgui.h"
#include "ui_base.h"
#include "menu_item.h"
#include "pch.h"
#include "utilities/application_data.h"

using namespace NAppData;

namespace NUI {
class NetToolPanel : public IMenuItem {
public:
  NetToolPanel();
  void render(std::unique_ptr<ApplicationData> &application_data);

private:
  bool mShowAnotherWindow;
  ImVec4 mClearColor;
};
} // namespace NUI