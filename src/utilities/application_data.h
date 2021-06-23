#pragma once
#include "nlohmann/json.hpp"
#include "pch.h"
#include <sstream>

using nlohmann::json;

namespace NAppData {

// From / To JSON converters

struct NetworkMessage {
  std::string name;
  std::string payload;
  NetworkMessage() { name = "Network Message", payload = ""; };
  NetworkMessage(std::string _payload) { payload = _payload; }
  enum type { BASE, BLUE_FRC, EMRG_TROOPS, EMRG_INJ, FREE_TXT };
  type message_type;
};

template <NetworkMessage::type T> struct type : NetworkMessage {
  type() { message_type = T; }
};

// map NetworkMessage values to JSON as strings
NLOHMANN_JSON_SERIALIZE_ENUM(NetworkMessage::type,
                             {
                                 {NetworkMessage::BASE, "BASE"},
                                 {NetworkMessage::BLUE_FRC, "BLUE_FRC"},
                                 {NetworkMessage::EMRG_INJ, "EMRG_INJ"},
                                 {NetworkMessage::EMRG_TROOPS, "EMRG_TROOPS"},
                             })

static void to_json(json &j, const NetworkMessage &m) {
  j = json{{"name", m.name},
           {"payload", m.payload},
           {"message_type", m.message_type}};
}

static void from_json(const json &j, NetworkMessage &m) {
  j.at("name").get_to(m.name);
  j.at("payload").get_to(m.payload);
  j.at("message_type").get_to(m.message_type);
}

// Definition of specific json message types
struct BlueForceMessage : type<NetworkMessage::BLUE_FRC> {
  BlueForceMessage(std::string _payload) {
    payload = _payload;
    name    = "Blue Force";
  }

  BlueForceMessage() {
    name    = "Blue Force";
    payload = "11111";
  };
};

struct EmergencyTroopsMessage : type<NetworkMessage::EMRG_TROOPS> {
  EmergencyTroopsMessage() {
    name    = "Emergency Troops";
    payload = "22222";
  }
};

struct EmergencyInjuredMessage : type<NetworkMessage::EMRG_INJ> {
  EmergencyInjuredMessage() {
    name    = "Emergency Injured";
    payload = "333333";
  }
};

struct FreeTextMessage : type<NetworkMessage::FREE_TXT> {
  FreeTextMessage() {
    name    = "Free Text Message";
    payload = "44444";
  }
};

class ApplicationData {
public:
  // Initialize application data state
  ApplicationData() { message_clicked = -1; };

  // Network Tool data
  std::vector<NetworkMessage> messages{
      BlueForceMessage("custom payload"), EmergencyTroopsMessage(),
      EmergencyInjuredMessage(), FreeTextMessage()};
  int message_clicked;
  bool udp_sender_started = false;

  void network_messages_from_json(const char *path);
  char multicast_ip[16] = "224.0.0.0";
  int multicast_port    = 5555;
};

} // namespace NAppData