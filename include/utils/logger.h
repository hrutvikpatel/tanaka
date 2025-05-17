#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <string>

namespace tanaka
{
  namespace utils
  {
    class Logger
    {
    public:
      static void init(const std::string &log_dir = "/var/log/tanaka");
      static void shutdown();

      // Helper methods for different log levels
      template <typename... Args>
      static void debug(const char *fmt, const Args &...args)
      {
        spdlog::debug(fmt, args...);
      }

      template <typename... Args>
      static void info(const char *fmt, const Args &...args)
      {
        spdlog::info(fmt, args...);
      }

      template <typename... Args>
      static void warn(const char *fmt, const Args &...args)
      {
        spdlog::warn(fmt, args...);
      }

      template <typename... Args>
      static void error(const char *fmt, const Args &...args)
      {
        spdlog::error(fmt, args...);
      }

      template <typename... Args>
      static void critical(const char *fmt, const Args &...args)
      {
        spdlog::critical(fmt, args...);
      }

    private:
      static bool initialized_;
    };
  }
}