#include "main_menu_bar.h"

namespace NUI {

MainMenuBar::MainMenuBar()
    : mShowAbout(false), mShowMetrics(false), mShowStyling(false){

                                              };

void MainMenuBar::render() {
  if (ImGui::BeginMainMenuBar()) {
    // Custom ranger tools
    if (ImGui::BeginMenu("Tools")) {
      for (const auto &menu_item : mMenuItems) {
        if (ImGui::MenuItem(menu_item->mMenuItemName.c_str(), nullptr,
                            &menu_item->mIsSelected, menu_item->mIsEnabled)) {
        }
      }
      ImGui::EndMenu();
    }

    // Miscellaneous static menu items
    if (ImGui::BeginMenu("Misc")) {
      if (ImGui::MenuItem("Metrics/UI Debugger", nullptr, &mShowMetrics)) {
      }

      if (ImGui::MenuItem("Window styling", nullptr, &mShowStyling)) {
      }

      if (ImGui::MenuItem("About")) {
      }

      ImGui::EndMenu();
    }
    ImGui::EndMainMenuBar();
  }

  // Show misc windows once we have obtained menu states
  if (mShowMetrics)
    ImGui::ShowMetricsWindow(&mShowMetrics);
  if (mShowStyling) {
    ImGui::Begin("Dear ImGui Style Editor", &mShowStyling);
    ImGui::ShowStyleEditor();
    ImGui::End();
  }
}

void MainMenuBar::add_menu_item(std::shared_ptr<IMenuItem> menu_item) {
  mMenuItems.push_back(menu_item);
}
} // namespace NUI