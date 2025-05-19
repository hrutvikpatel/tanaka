#pragma once
#include <string>
#include <unordered_map>
#include <stdexcept>
#include <vector>

namespace tanaka::config
{
  class ConfigError : public std::runtime_error
  {
  public:
    explicit ConfigError(const std::string &msg) : std::runtime_error(msg) {}
  };

  class Config
  {
  public:
    Config() = default;

    void load(const std::string &filepath);

    std::string get(const std::string &key) const;
    std::string get_active_provider() const;

  private:
    std::string active_provider_;
    std::unordered_map<std::string, std::string> provider_config_;

    static std::vector<std::string> required_fields_for(const std::string &provider);
  };
}