#pragma once
#include "utilities/data.h"
#include <string>

namespace NWindow {
class IWindow {
public:
  virtual void *get_native_window() = 0;
  virtual void set_native_window(void *window) = 0;
  virtual void on_close() = 0;
  virtual void on_resize(int width, int height) = 0;
  int Width;
  int Height;
  Vec4 clear_color;
  std::string title;
};
} // namespace NWindow