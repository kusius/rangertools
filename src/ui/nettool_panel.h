#pragma once

#include "imgui/ImGuiFileDialog.h"
#include "imgui/imgui.h"
#include "menu_item.h"
#include "pch.h"
#include "ui_base.h"
#include "utilities/application_data.h"

using namespace NAppData;

namespace NUI {
class NetToolPanel : public IMenuItem {
public:
  NetToolPanel();
  void render(std::unique_ptr<ApplicationData> &application_data);

private:
  // Sender UI
  void make_udp_sender_ui(std::unique_ptr<ApplicationData> &application_data);
  void
  make_interface_selection(std::unique_ptr<ApplicationData> &application_data);
  void make_message_buttons(std::unique_ptr<ApplicationData> &application_data);
  void make_file_chooser(std::unique_ptr<ApplicationData> &application_data);

  // Receiver UI
  void make_udp_receiver_ui(std::unique_ptr<ApplicationData> &application_data);

  bool mShowAnotherWindow;
  ImVec4 mClearColor;
};
} // namespace NUI