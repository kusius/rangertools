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

  make_interface_selection(application_data);

  make_file_chooser(application_data);

  make_message_buttons(application_data);
}

inline void NetToolPanel::make_interface_selection(
    std::unique_ptr<ApplicationData> &application_data) {
  auto interfaces      = application_data->interfaces;
  int selectable_flags = (application_data->udp_sender_started)
                             ? (ImGuiSelectableFlags_Disabled)
                             : 0;

  int interface_selected        = application_data->interface_selected;
  std::string default_selection = "None";
  if (!application_data->interfaces.empty() &&
      interface_selected < interfaces.size()) {
    default_selection = interfaces.at(interface_selected).ipv4_address;
  }

  if (ImGui::BeginCombo("Network Interfaces", default_selection.c_str())) {
    application_data->interface_selection = true;
    for (int n = 0; n < interfaces.size(); n++) {

      const bool is_selected = (application_data->interface_selected == n);

      if (ImGui::Selectable(interfaces.at(n).name.c_str(), is_selected,
                            selectable_flags))
        application_data->interface_selected = n;

      // Set the initial focus when opening the combo (scrolling + keyboard
      // navigation focus)
      if (is_selected)
        ImGui::SetItemDefaultFocus();
    }
    ImGui::EndCombo();
  } else {
    application_data->interface_selection = false;
  }
}

inline void NetToolPanel::make_message_buttons(
    std::unique_ptr<ApplicationData> &application_data) {
  auto messages     = application_data->messages;
  int buttons_count = 9;
  ImVec2 button_size(40, 40);

  // Buttons for different message types
  for (int i = 0; i < messages.size(); ++i) {
    ImGuiStyle &style = ImGui::GetStyle();
    ImGui::PushID(i);

    if (ImGui::Button(messages.at(i).name.c_str())) {
      application_data->set_clicked_message(i);
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

inline void NetToolPanel::make_file_chooser(
    std::unique_ptr<ApplicationData> &application_data) {
  // File dialog
  if (ImGui::Button("Import from file")) {
    ImGuiFileDialog::Instance()->OpenModal("ChooseFileDlgKey", "Choose File",
                                           ".json", ".");
  }

  if (ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey")) {
    // action if OK
    if (ImGuiFileDialog::Instance()->IsOk()) {
      application_data->message_file_path =
          ImGuiFileDialog::Instance()->GetFilePathName();
      application_data->network_messages_from_json(
          application_data->message_file_path.c_str());
    }

    // close
    ImGuiFileDialog::Instance()->Close();
  }

  // Refresh file loading button
  ImGui::SameLine();
  ImGui::Text(application_data->message_file_path.c_str());
  ImGui::SameLine();
  if (ImGui::Button("Reload")) {
    application_data->network_messages_from_json(
        application_data->message_file_path.c_str());
  }
}

inline void NetToolPanel::make_udp_receiver_ui(
    std::unique_ptr<ApplicationData> &application_data) {
  ImGui::NewLine();
  ImGui::Text("UDP multicast receiver");
  ImGui::Separator();
}

} // namespace NUI