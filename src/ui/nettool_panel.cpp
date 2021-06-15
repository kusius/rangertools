#include "nettool_panel.h"
#include <iostream>

using namespace NAppData;

namespace NUI {

NetToolPanel::NetToolPanel()
    : mShowAnotherWindow(false),
      mClearColor(ImVec4(0.45f, 0.55f, 0.60f, 1.00f)) {
  mMenuItemName = "Network Tool";
  mIsEnabled    = true;
  mIsSelected   = false;
}

void NetToolPanel::render(std::unique_ptr<ApplicationData> &application_data) {
  {
    if (!mIsSelected)
      return;

    auto messages              = application_data->messages;
    unsigned int buttons_count = 9;
    ImVec2 button_size(40, 40);
    ImGui::Begin("NetTool");

    for (int i = 0; i < messages.size(); ++i) {
      ImGuiStyle &style = ImGui::GetStyle();
      ImGui::PushID(i);

      if (ImGui::Button(messages.at(i).name.c_str())) {
        std::cout << "Pushed button " << i << " " << messages.at(i).payload
                  << " " << messages.at(i).message_type << std::endl;
        application_data->message_clicked = i;
      }

      float last_button_x2 = ImGui::GetItemRectMax().x;
      float next_button_x2 =
          last_button_x2 + style.ItemSpacing.x + button_size.x;
      float window_visible_x2 =
          ImGui::GetWindowPos().x + ImGui::GetWindowContentRegionMax().x;
      if (i + 1 < buttons_count && next_button_x2 < window_visible_x2)
        ImGui::SameLine();

      ImGui::PopID();
    }

    ImGui::End();
  }
}
} // namespace NUI