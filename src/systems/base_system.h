#pragma once

#include "pch.h"
#include "utilities/application_data.h"


using namespace NAppData;

namespace NSystem {

class IBaseSystem {
public:
  virtual void update(std::unique_ptr<ApplicationData> &application_data) = 0;
};

} // namespace NSystem