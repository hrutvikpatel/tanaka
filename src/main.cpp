#include <iostream>
#include "utils/logger.h"
#include "ui.h" // CLI wrapper with UI class

const std::string LOG_DIR = std::string(getenv("HOME")) + "/.tanaka/logs";

int main(int argc, char **argv)
{
  try
  {
    // Initialize logger
    tanaka::utils::Logger::init(LOG_DIR);
    tanaka::utils::Logger::info("Starting Tanaka daemon CLI");

    tanaka::ui::UI::init();
    tanaka::ui::UI::run(argc, argv);

    return 0;
  }
  catch (const std::exception &e)
  {
    std::cerr << "Error: " << e.what() << std::endl;
    tanaka::utils::Logger::error(e.what());
    return 1;
  }
}