#pragma once
#include <CLI/CLI.hpp>
#include <map>
#include <string>
#include <vector>

namespace tanaka
{
  namespace ui
  {

    class UI
    {
    public:
      static void init();
      static void run(int argc, char **argv);

    private:
      static CLI::App app;
      static void configure_command(CLI::App &app);
      static void configure_provider();
      static std::string prompt_for_input(const std::string &prompt);

    public:
      static const std::map<std::string, std::pair<std::string, std::vector<std::pair<std::string, std::string>>>> PROVIDERS;
    };

  }
}