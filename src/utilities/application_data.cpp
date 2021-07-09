#include "application_data.h"
#include <fstream>

namespace NAppData {

void ApplicationData::network_messages_from_json(const char *path) {
  // Try to read and parse the json file into messages
  std::ifstream file(path);
  if (file.is_open() && !file.fail()) {
    messages.clear();

    try {
      json j = json::parse(file);

      if (j.is_array()) {

        for (json j_object : j) {
          NetworkMessage message = j_object.get<NetworkMessage>();
          messages.push_back(message);
        }

      } else {

        NetworkMessage message = j.get<NetworkMessage>();
        messages.push_back(message);
      }
    } catch (json::exception exception) {
      NSystem::Logger::getInstance()->write(NSystem::Logger::Level::ERR,
                                            exception.what());
    }
  }
}

bool ApplicationData::get_clicked_message(NetworkMessage &out) {
  if (message_clicked >= 0 && message_clicked < messages.size()) {
    out             = messages.at(message_clicked);
    message_clicked = -1;
    return true;
  } else {
    out = {};
    return false;
  }
}

void ApplicationData::set_clicked_message(int index) {
  message_clicked = index;
}

bool ApplicationData::get_selected_interface(NetworkInterface &out) {
  if (interface_selected >= 0 && interface_selected < interfaces.size()) {
    out = interfaces.at(interface_selected);
    return true;
  } else {
    out = {};
    return false;
  }
}

} // namespace NAppData