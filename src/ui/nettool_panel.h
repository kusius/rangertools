#pragma once

#include "imgui/imgui.h"
#include "pch.h"
#include "utilities/application_data.h"
#include <string>
#include <vector>

using namespace NAppData;

namespace NUI {
class NetToolPanel {
public:
  NetToolPanel();
  void render(std::unique_ptr<ApplicationData> &application_data);

private:
  bool mShowAnotherWindow;
  ImVec4 mClearColor;
};
} // namespace NUI