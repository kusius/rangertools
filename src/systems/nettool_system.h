#include "base_system.h"
#include "udp_sender.h"
#include <thread>

namespace NSystem {

class NetToolSystem : public IBaseSystem {
public:
  NetToolSystem();
  ~NetToolSystem();
  void update(std::unique_ptr<ApplicationData> &application_data) override;
  void shutdown() override;

private:
  std::unique_ptr<UdpSender> udp_sender;
};

} // namespace NSystem