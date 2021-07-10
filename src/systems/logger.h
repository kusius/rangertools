#pragma once
#include "imgui/imgui.h"
#include "map"
#include "pch.h"
#include "utilities/data.h"
#include <chrono>

namespace NSystem {
struct LogItemColorInfo {
  bool has_color = false;
  Vec4 color;
};

class Logger {
public:
  enum class Target : short {
    DISABLED = 1,
    STDOUT   = 2,
    STDERR   = 3,
    LOG_FILE = 4
  };

  enum class Level : short {
    DEBUG   = 1,
    INFO    = 2,
    NOTICE  = 3,
    WARNING = 4,
    ERR     = 5,
    CRIT    = 6,
    ALERT   = 7,
    EMERG   = 8
  };

  static std::shared_ptr<Logger> getInstance();

  void write(Level level, const char *fmt, ...) IM_FMTARGS(2);

  void log_info(const char *info);

  void log_error(const char *error);

  void clear();

  ImGuiTextBuffer &get_buffer();

  std::vector<int> &get_line_offsets();

  std::vector<LogItemColorInfo> &get_line_colors();

protected:
  Logger(){};

private:
  static std::shared_ptr<Logger> Log;

  std::string level_to_string(Level level);

  LogItemColorInfo level_to_color(const Level &level);

  bool timestamp_enabled = true;
  bool level_enabled     = true;

  ImGuiTextBuffer buffer;
  std::vector<int> line_offsets;
  std::vector<LogItemColorInfo> line_colors;

  // String representations of log levels
  std::map<Level, std::string> level_map = {{Level::DEBUG, "DEBUG"},
                                            {Level::INFO, "INFO"},
                                            {Level::WARNING, "WARNING"},
                                            {Level::ERR, "ERROR"},
                                            {Level::CRIT, "CRITICAL"}};

  std::map<Level, Vec4> level_color_map = {
      {Level::DEBUG, Vec4(0.99f, 0.96f, 0.012f, 1.0f)},
      {Level::WARNING, Vec4(0.99f, 0.66f, 0.012f, 1.0f)},
      {Level::ERR, Vec4(0.99f, 0.012f, 0.73f, 1.0f)},
      {Level::CRIT, Vec4(1.0f, 0.0f, 0.0f, 1.0f)},
  };
};
} // namespace NSystem