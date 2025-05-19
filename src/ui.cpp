#include "ui.h"
#include <iostream>

namespace tanaka
{
  namespace ui
  {

    // Define the static app
    CLI::App UI::app{"Tanaka - File Backup CLI"};

    const std::map<std::string, std::pair<std::string, std::vector<std::pair<std::string, std::string>>>> UI::PROVIDERS = {
        {"1", {"Digital Ocean Spaces", {{"token", "Enter your Digital Ocean API token: "}, {"region", "Enter your Space region (e.g., nyc3): "}, {"bucket", "Enter your Space bucket name: "}}}},
        {"2", {"AWS S3", {{"access_key", "Enter your AWS Access Key: "}, {"secret_key", "Enter your AWS Secret Key: "}, {"region", "Enter your AWS region (e.g., us-east-1): "}, {"bucket", "Enter your S3 bucket name: "}}}},
        {"3", {"Google Cloud Storage", {{"credentials_file", "Enter path to your GCP credentials file: "}, {"bucket", "Enter your GCS bucket name: "}}}}};

    void UI::init()
    {
      configure_command(app);
    }

    void UI::run(int argc, char **argv)
    {
      try
      {
        app.require_subcommand();
        app.parse(argc, argv);
      }
      catch (const CLI::ParseError &e)
      {
        std::exit(app.exit(e));
      }
    }

    void UI::configure_command(CLI::App &app)
    {
      app.add_subcommand("configure", "Configure cloud provider")
          ->callback([]()
                     { configure_provider(); });
    }

    void UI::configure_provider()
    {
      std::cout << "Available providers:\n";
      for (const auto &[id, data] : PROVIDERS)
      {
        std::cout << "  [" << id << "] " << data.first << '\n';
      }

      std::cout << "\nSelect provider by number: ";
      std::string choice;
      std::getline(std::cin, choice);

      if (PROVIDERS.find(choice) == PROVIDERS.end())
      {
        std::cout << "Invalid selection.\n";
        return;
      }

      const auto &[provider_name, fields] = PROVIDERS.at(choice);
      std::map<std::string, std::string> user_inputs;

      std::cout << "\nConfiguring: " << provider_name << "\n";
      for (const auto &[key, prompt] : fields)
      {
        user_inputs[key] = prompt_for_input(prompt);
      }

      std::cout << "\nCollected configuration:\n";
      for (const auto &[key, value] : user_inputs)
      {
        std::cout << "  " << key << ": " << value << '\n';
      }

      // TODO: Save to config file
    }

    std::string UI::prompt_for_input(const std::string &prompt)
    {
      std::string input;
      std::cout << prompt;
      std::getline(std::cin, input);
      return input;
    }

  }
}