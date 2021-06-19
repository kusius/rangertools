#pragma once

#ifdef _WIN32
#define _WIN32_WINNT 0x0A00
#endif

#define ASIO_STANDALONE
#include "asio/asio.hpp"
#include "asio/post.hpp"
#include "asio/ts/buffer.hpp"
#include "asio/ts/internet.hpp"
#include <iostream>
#include <mutex>
#include <queue>
#include <sstream>
#include <string>

namespace NSystem {

class UdpSender {
public:
  UdpSender();
  ~UdpSender();
  bool init(const std::string &ip_address, const int &port);
  void start();
  void stop();
  void enqueue_message(const std::string &message);
  bool stopped() { return state == STOPPED; }

private:
  enum STATE { INITIALIZED, RUNNING, STOPPED };
  STATE state;
  void log_error(const asio::error_code &ec);
  void do_send();

  std::unique_ptr<asio::io_context> io_context;
  std::unique_ptr<asio::ip::udp::socket> socket;
  std::unique_ptr<asio::ip::udp::endpoint> endpoint;

  std::unique_ptr<std::queue<std::string>> data_queue;
  std::shared_ptr<std::mutex> data_mutex;
  std::thread thread;

  std::mutex exit_mutex;
  std::promise<void> exit_promise;
  std::future<void> exit_future;
};

} // namespace NSystem