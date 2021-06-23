#include "nettool_system.h"

namespace NSystem {

NetToolSystem::NetToolSystem() {
  is_active  = false;
  udp_sender = std::make_unique<UdpSender>();
}

void NetToolSystem::update(std::unique_ptr<ApplicationData> &application_data) {
  bool udp_sender_should_run = application_data->udp_sender_started;

  if (udp_sender_should_run) {

    if (udp_sender->stopped()) {

      udp_sender->init(application_data->multicast_ip,
                       application_data->multicast_port);
      udp_sender->start();
    }
  } else if (!udp_sender->stopped()) {

    udp_sender->stop();
  }

  if (!udp_sender->stopped()) {
    if (application_data->message_clicked >= 0) {
      std::string message =
          application_data->messages.at(application_data->message_clicked)
              .payload;
      application_data->message_clicked = -1;
      udp_sender->enqueue_message(message);
    }
  }
}

void NetToolSystem::shutdown() { udp_sender.release(); }

} // namespace NSystem