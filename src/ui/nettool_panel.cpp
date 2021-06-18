#include "nettool_panel.h"

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

  if (!mIsSelected)
    return;

    // Input for UDP multicast address
    ImGui::InputText("UDP Multicast address", application_data->multicast_ip, IM_ARRAYSIZE(application_data->multicast_ip));
    ImGui::InputInt("UDP Multicast port", &(application_data->multicast_port));

    // Buttons for different message types
    for (int i = 0; i < messages.size(); ++i) {
      ImGuiStyle &style = ImGui::GetStyle();
      ImGui::PushID(i);

  if (ImGui::Button("Import from file")) {
    application_data->network_messages_from_json("messages.json");
  }

  for (int i = 0; i < messages.size(); ++i) {
    ImGuiStyle &style = ImGui::GetStyle();
    ImGui::PushID(i);

    if (ImGui::Button(messages.at(i).name.c_str())) {
      std::cout << "Pushed button " << i << " " << messages.at(i).payload << " "
                << messages.at(i).message_type << std::endl;
      application_data->message_clicked = i;
    }

    float last_button_x2 = ImGui::GetItemRectMax().x;
    float next_button_x2 = last_button_x2 + style.ItemSpacing.x + button_size.x;
    float window_visible_x2 =
        ImGui::GetWindowPos().x + ImGui::GetWindowContentRegionMax().x;
    if (i + 1 < buttons_count && next_button_x2 < window_visible_x2)
      ImGui::SameLine();

    ImGui::PopID();
  }

  ImGui::End();
}
} // namespace NUI