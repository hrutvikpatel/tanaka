#include <iostream>
#include "utils/logger.h"
#include "config/config.h"

const std::string LOG_DIR = std::string(getenv("HOME")) + "/.tanaka/logs";
const std::string CONFIG_PATH = std::string(getenv("HOME")) + "/.tanaka/config.toml";
const std::string DB_PATH = std::string(getenv("HOME")) + "/.tanaka/data.db";

int main(int argc, char **argv)
{
  using namespace tanaka::utils;
  using namespace tanaka::config;
  try
  {
    // Initialize logger
    Logger::init(LOG_DIR);
    Logger::info("Starting Tanaka daemon CLI");

    Config config;
    config.load(CONFIG_PATH);

    Logger::info("Config successfully loaded!");
    Logger::info("Provider: {}", config.get_active_provider());

    return 0;
  }
  catch (const std::exception &e)
  {
    std::cerr << "Error: " << e.what() << std::endl;
    tanaka::utils::Logger::error(e.what());
    return 1;
  }
}