#pragma once
#include "data_models.h"
#include "systems/logger.h"
#include <sstream>

namespace NAppData {

class ApplicationData {
public:
  // Network Tool data
  std::vector<NetworkMessage> messages{
      BlueForceMessage("custom payload"), EmergencyTroopsMessage(),
      EmergencyInjuredMessage(), FreeTextMessage()};

  std::vector<NetworkInterface> interfaces;

  int interface_selected   = -1;
  bool udp_sender_started  = false;
  bool interface_selection = false;

  void network_messages_from_json(const char *path);

  bool get_clicked_message(NetworkMessage &out);
  void set_clicked_message(int index);
  bool get_selected_interface(NetworkInterface &out);
  void set_selected_interface(int index);

  char multicast_ip[16] = "224.0.0.0";
  int multicast_port    = 5555;

private:
  int message_clicked = -1;
};

} // namespace NAppData