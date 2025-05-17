#pragma once

#include <string>
#include <vector>
#include <map>
#include "CLI/CLI.hpp"

namespace tanaka
{
  namespace ui
  {
    class UI
    {
    public:
      static void run(int argc, char **argv);

    private:
      static void configure_command(CLI::App &app);
      static void configure_provider();
      static std::string prompt_for_input(const std::string &prompt);

      static const std::map<std::string, std::pair<std::string, std::vector<std::pair<std::string, std::string>>>> PROVIDERS;
    };
  }
}