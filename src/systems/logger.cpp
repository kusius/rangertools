#include "logger.h"

namespace NSystem {
std::shared_ptr<Logger> Logger::Log;

std::shared_ptr<Logger> Logger::getInstance() {
  if (!Log) {
    Log = std::shared_ptr<Logger>(new Logger());
    Log->clear();
  }

  return Log;
}

void Logger::log_info(const char *info) { write(Level::INFO, info); }

void Logger::log_error(const char *error) { write(Level::ERR, error); }

void Logger::clear() {
  buffer.clear();
  line_offsets.clear();
  line_offsets.push_back(0);

  line_colors.clear();
  line_colors.push_back({true, Vec4(1.0f, 0.0f, 0.0f, 1.0f)});
}

void Logger::write(Level level, const char *fmt, ...) IM_FMTARGS(2) {
  int old_size = buffer.size();
  va_list args;

  va_start(args, fmt);

  std::string to_log(fmt);
  LogItemColorInfo color_info = {};

  if (this->level_enabled) {
    to_log     = "[" + this->level_to_string(level) + "] " + to_log;
    color_info = level_to_color(level);
  }

  if (this->timestamp_enabled) {
    std::time_t time =
        std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    struct tm *timeStruct = std::localtime(&time);

    char timeStr[80];
    strftime(timeStr, 80, "%d/%b/%Y:%H:%M:%S", timeStruct);
    to_log = " [" + std::string(timeStr) + "] " + to_log;
  }

  if (to_log.back() != '\n')
    to_log += '\n';

  buffer.appendfv(to_log.c_str(), args);

  va_end(args);

  for (int new_size = buffer.size(); old_size < new_size; old_size++) {
    if (buffer[old_size] == '\n') {
      line_offsets.push_back(old_size + 1);
      line_colors.push_back(color_info);
    }
  }
}

ImGuiTextBuffer &Logger::get_buffer() { return buffer; }

std::vector<int> &Logger::get_line_offsets() { return line_offsets; }

std::vector<LogItemColorInfo> &Logger::get_line_colors() { return line_colors; }

std::string Logger::level_to_string(Level level) { return level_map[level]; }

LogItemColorInfo Logger::level_to_color(const Level &level) {
  auto it = level_color_map.find(level);
  if (it != level_color_map.end()) {
    return {true, it->second};
  } else {
    return {false, Vec4()};
  }
}

} // namespace NSystem