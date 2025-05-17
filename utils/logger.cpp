#include "logger.h"
#include <filesystem>
#include <memory>
#include <stdexcept>

namespace tanaka {
  namespace utils {
    bool Logger::initialized_ = false;

    void Logger::init(const std::string& log_dir) {
      if (initialized_) return;

      try {
        // Create log dir if it doesn't exist
        if (!std::filesystem::exists(log_dir)) {
          std::filesystem::create_directories(log_dir);
        }

        auto rotating_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(
          log_dir + "/tanaka.log",
          1024 * 1024,
          2
        );

        // Create logger
        auto logger = std::make_shared<spdlog::logger>("tanaka", rotating_sink);

        // Set log pattern
        logger->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%l] [%t] %v");

        // Set as default logger
        spdlog::set_default_logger(logger);

        initialized_ = true;
        spdlog::info("Logger initialized");
      } catch (const std::exception& e) {
        throw std::runtime_error("Failed to initialize logger: " + std::string(e.what()));
      }
    }

    void Logger::shutdown() {
      if (initialized_) {
        spdlog::shutdown();
        initialized_ = false;
      }
    }
  }
}