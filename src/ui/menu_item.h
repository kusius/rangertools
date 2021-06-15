#pragma once
#include "pch.h"

namespace NUI {

class IMenuItem {
public:
  std::string mMenuItemName;
  bool mIsSelected;
  bool mIsEnabled;
};

} // namespace NUI