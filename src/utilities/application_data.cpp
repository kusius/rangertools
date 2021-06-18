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
    } catch (std::exception exception) {
      // TODO: Logger mechanism
      std::cout << exception.what() << std::endl;
    }
  }
}

} // namespace NAppData