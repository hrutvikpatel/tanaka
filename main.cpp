#include <iostream>
#include "utils/logger.h"

const std::string LOG_DIR = std::string(getenv("HOME")) + "/.tanaka/logs";

int main() {
  try {
    // Initialize logger
    tanaka::utils::Logger::init(LOG_DIR);

    // Test log message
    tanaka::utils::Logger::info("Hello world!");

    return 0;
  } catch (const std::exception& e) {
    std::cerr << "Failed to initialize logger: " << e.what() << std::endl;
    return 1;
  }
}