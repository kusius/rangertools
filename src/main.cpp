#include "application.h"
#include "pch.h"

int main(int, char **) {
  auto app = std::make_unique<Application>("Ranger Tools");
  app->loop();
  return 0;
}
