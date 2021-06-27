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

  ImGui::Begin("NetTool", &mIsSelected);

  make_udp_sender_ui(application_data);

  make_udp_receiver_ui(application_data);

  ImGui::End();
}

inline void NetToolPanel::make_udp_sender_ui(
    std::unique_ptr<ApplicationData> &application_data) {
  auto messages     = application_data->messages;
  int buttons_count = 9;
  ImVec2 button_size(40, 40);

  ImGui::Text("UDP multicast sender");
  ImGui::SameLine();
  ImGui::Checkbox("Start", &application_data->udp_sender_started);
  ImGui::Separator();

  // Input for UDP multicast address
  int flags = (application_data->udp_sender_started)
                  ? (ImGuiInputTextFlags_ReadOnly)
                  : 0;
  ImGui::InputTextWithHint("UDP Multicast address", "192.168.1.1",
                           application_data->multicast_ip,
                           IM_ARRAYSIZE(application_data->multicast_ip), flags);
  ImGui::InputInt("UDP Multicast port", &(application_data->multicast_port), 1,
                  100, flags);

  // File dialog
  if (ImGui::Button("Import from file")) {
    ImGuiFileDialog::Instance()->OpenModal("ChooseFileDlgKey", "Choose File",
                                           ".json", ".");
  }

  if (ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey")) {
    // action if OK
    if (ImGuiFileDialog::Instance()->IsOk()) {
      std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
      application_data->network_messages_from_json(filePathName.c_str());
    }

    // close
    ImGuiFileDialog::Instance()->Close();
  }

  // Buttons for different message types
  for (int i = 0; i < messages.size(); ++i) {
    ImGuiStyle &style = ImGui::GetStyle();
    ImGui::PushID(i);

    if (ImGui::Button(messages.at(i).name.c_str())) {
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
}

inline void NetToolPanel::make_udp_receiver_ui(
    std::unique_ptr<ApplicationData> &application_data) {
  ImGui::NewLine();
  ImGui::Text("UDP multicast receiver");
  ImGui::Separator();
}

} // namespace NUI