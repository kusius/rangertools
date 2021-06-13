#include "base_system.h"

namespace NSystem {

class NetToolSystem : public IBaseSystem {
public:
  void update(std::unique_ptr<ApplicationData> &application_data) override;
};

} // namespace NSystem