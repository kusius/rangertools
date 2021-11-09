#include "logger_panel.h"

namespace NUI {

const float verticalPercentPlacement = 0.35f;

LoggerPanel::LoggerPanel()

{
  mMenuItemName = "Global log";
  mIsEnabled    = true;
  mIsSelected   = false;
}

void LoggerPanel::render(int windowWidth, int windowHeight) {
  if (!mIsSelected)
    return;

  float panelHeight = (verticalPercentPlacement * windowHeight);
  // Make the size of the panel fill the window length-wise and
  ImGui::SetNextWindowSize(ImVec2((float)windowWidth, panelHeight));
  ImGui::SetNextWindowPos(ImVec2(0, (float)windowHeight - panelHeight));
  // Begin drawing the window
  if (!ImGui::Begin("Global log", &mIsSelected,
                    ImGuiWindowFlags_NoResize |
                        ImGuiWindowFlags_NoDecoration)) {
    ImGui::End();
    return;
  }

  // Options menu
  if (ImGui::BeginPopup("Options")) {
    ImGui::Checkbox("Auto-scroll", &auto_scroll);
    ImGui::EndPopup();
  }

  // Main window
  if (ImGui::Button("Options"))
    ImGui::OpenPopup("Options");
  ImGui::SameLine();
  bool clear = ImGui::Button("Clear");
  ImGui::SameLine();
  bool copy = ImGui::Button("Copy");
  ImGui::SameLine();
  filter.Draw("Filter", -100.0f);

  ImGui::Separator();
  ImGui::BeginChild("scrolling", ImVec2(0, 0), false,
                    ImGuiWindowFlags_HorizontalScrollbar);

  std::shared_ptr<NSystem::Logger> logger = NSystem::Logger::getInstance();

  ImGuiTextBuffer buffer        = logger->get_buffer();
  std::vector<int> line_offsets = logger->get_line_offsets();
  std::vector<NSystem::LogItemColorInfo> line_colors =
      logger->get_line_colors();

  if (clear)
    logger->clear();
  if (copy)
    ImGui::LogToClipboard();
  std::cout << "This is a test string" << std::endl;

  ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
  const char *buf     = buffer.begin();
  const char *buf_end = buffer.end();
  if (filter.IsActive()) {
    for (int line_no = 0; line_no < line_offsets.size(); line_no++) {
      const char *line_start = buf + line_offsets[line_no];
      const char *line_end   = (line_no + 1 < line_offsets.size())
                                   ? (buf + line_offsets[line_no + 1] - 1)
                                   : buf_end;
      if (filter.PassFilter(line_start, line_end)) {
        auto color_info = (line_no + 1 < line_offsets.size())
                              ? line_colors[line_no + 1]
                              : line_colors[0];

        if (color_info.has_color)
          ImGui::PushStyleColor(ImGuiCol_Text, color_info.color);
        ImGui::TextUnformatted(line_start, line_end);
        if (color_info.has_color)
          ImGui::PopStyleColor();
      }
    }
  } else {
    ImGuiListClipper clipper;
    clipper.Begin(line_offsets.size());
    while (clipper.Step()) {
      for (int line_no = clipper.DisplayStart; line_no < clipper.DisplayEnd;
           line_no++) {
        const char *line_start = buf + line_offsets[line_no];
        const char *line_end   = (line_no + 1 < line_offsets.size())
                                     ? (buf + line_offsets[line_no + 1] - 1)
                                     : buf_end;

        auto color_info = (line_no + 1 < line_offsets.size())
                              ? line_colors[line_no + 1]
                              : line_colors[0];

        if (color_info.has_color)
          ImGui::PushStyleColor(ImGuiCol_Text, color_info.color);
        ImGui::TextUnformatted(line_start, line_end);
        if (color_info.has_color)
          ImGui::PopStyleColor();
      }
    }
    clipper.End();
  }
  ImGui::PopStyleVar();

  if (auto_scroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
    ImGui::SetScrollHereY(1.0f);

  ImGui::EndChild();
  ImGui::End();
}

} // namespace NUI