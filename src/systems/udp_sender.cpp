#include "udp_sender.h"

const int max_message_count = 100000;

namespace NSystem {
UdpSender::UdpSender() : state(STOPPED) {
  io_context = std::make_unique<asio::io_context>();
  data_mutex = std::make_shared<std::mutex>();
  data_queue = std::make_unique<std::queue<std::string>>();
};

UdpSender::~UdpSender() { stop(); }

void UdpSender::do_send() {
  Logger::getInstance()->log_info("do_send()");
  // Grab a message from the data queue and send it through the socket
  std::unique_lock<std::mutex> lock(*data_mutex);
  if (!data_queue->empty()) {
    std::string *message = new std::string(data_queue->front());

    data_queue->pop();

    socket->async_send_to(asio::buffer(std::move(*message)), *endpoint,
                          [this](std::error_code ec, std::size_t length) {
                            if (ec) {
                              Logger::getInstance()->log_error(
                                  ec.message().c_str());
                            }
                          });
  }

  lock.unlock();
}

bool UdpSender::init(const std::string &ip_address, const int &port,
                     const NAppData::NetworkInterface &interface) {
  if (state == RUNNING)
    stop();

  asio::error_code ec;

  auto multicast_address = asio::ip::make_address(ip_address, ec);
  if (ec) {
    std::stringstream message;
    message << "Error parsing address: " + ip_address;
    Logger::getInstance()->log_error(message.str().c_str());
    return false;
  }

  endpoint = std::make_unique<asio::ip::udp::endpoint>(multicast_address, port);
  socket   = std::make_unique<asio::ip::udp::socket>(*io_context,
                                                   endpoint->protocol());

  auto local_interface =
      asio::ip::address_v4::from_string(interface.ipv4_address, ec);
  if (!ec) {
    asio::ip::multicast::outbound_interface option(local_interface);
    socket->set_option(option);
  } else {
    Logger::getInstance()->write(
        Logger::Level::WARNING,
        "UDP sender running with no outbound interface");
  }

  state = INITIALIZED;
  return true;
}

void UdpSender::start() {
  if (state != INITIALIZED)
    return;

  if (io_context->stopped())
    io_context->restart();

  // You only make a promise once
  exit_promise.swap(std::promise<void>());
  exit_future = exit_promise.get_future();

  thread = std::thread([this]() {
    auto work = asio::require(io_context->get_executor(),
                              asio::execution::outstanding_work.tracked);
    io_context->run();
    {
      std::lock_guard<std::mutex> lock(exit_mutex);
      exit_promise.set_value();
    }
    Logger::getInstance()->log_info("Asio thread finished OK");
  });

  thread.detach();
}

void UdpSender::stop() {
  io_context->stop();
  auto exit_status = exit_future.wait_for(std::chrono::seconds(3));
  if (exit_status == std::future_status::timeout)
    Logger::getInstance()->log_error("Asio thread exit timeout");
  state = STOPPED;
}

void UdpSender::enqueue_message(const std::string &message) {
  {
    std::lock_guard<std::mutex> lock(*data_mutex);
    data_queue->push(message);
  }
  asio::post(*io_context, [this] { do_send(); });
}

std::vector<NAppData::NetworkInterface> UdpSender::get_avaible_interfaces() {
  using asio::ip::tcp;
  asio::io_service io_service;
  tcp::resolver resolver(io_service);
  tcp::resolver::query query(asio::ip::host_name(), "");
  tcp::resolver::iterator it = resolver.resolve(query);

  std::vector<NAppData::NetworkInterface> interfaces;

  while (it != tcp::resolver::iterator()) {
    asio::ip::address address = it->endpoint().address();
    it++;
    if (address.is_v4()) {
      interfaces.push_back({address.to_string(), address.to_string()});
    }
  }

  return interfaces;
}

} // namespace NSystem