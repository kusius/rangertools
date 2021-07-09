#include "nettool_system.h"

namespace NSystem {

NetToolSystem::NetToolSystem() {
  is_active  = false;
  udp_sender = std::make_unique<UdpSender>();
}

NetToolSystem::~NetToolSystem() { shutdown(); }

void NetToolSystem::update(std::unique_ptr<ApplicationData> &application_data) {
  bool udp_sender_should_run = application_data->udp_sender_started;

  // TODO: Maybe we should extend UdpSender to do these things
  // automatically instead of being managed by external user-classes
  if (udp_sender_should_run) {

    if (udp_sender->stopped()) {
      NetworkInterface interface = {};
      application_data->get_selected_interface(interface);
      bool ok = udp_sender->init(application_data->multicast_ip,
                                 application_data->multicast_port, interface);
      if (ok) {
        udp_sender->start();
      } else {
        // Set the application data UI state to false
        // because we could not start the sender
        application_data->udp_sender_started = false;
      }
    }
  } else if (!udp_sender->stopped()) {
    // TODO: Put logic in appdata function
    udp_sender->stop();
  }

  if (application_data->interface_selection) {
    application_data->interfaces = udp_sender->get_avaible_interfaces();
  }

  // We get the message clicked in the UI and send it
  if (!udp_sender->stopped()) {
    NetworkMessage message;
    if (application_data->get_clicked_message(message)) {
      udp_sender->enqueue_message(message.payload);
    }
  }
}

void NetToolSystem::shutdown() { udp_sender.release(); }

} // namespace NSystem