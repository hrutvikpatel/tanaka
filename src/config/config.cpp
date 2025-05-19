#include "config/config.h"
#include <toml++/toml.hpp>

namespace tanaka::config
{
  void Config::load(const std::string& filepath) {
    auto content = toml::parse_file(filepath);

    auto provider = content["provider"];
    if (!provider || !provider["active"]) {
      throw ConfigError("Missing [provider] or 'active' field.");
    }

    active_provider_ = provider["active"].value_or("");
    auto provider_details = content[active_provider_];
    if (!provider_details.is_table()) {
      throw ConfigError("Missing section for providers: [" + active_provider_ + "]");
    }

    for (const auto& key : required_fields_for(active_provider_)) {
      provider_config_[key] = provider_details[key].value_or("");
      if (provider_config_.at(key).empty()) {
        throw ConfigError("Missing required field for provider '"  + active_provider_ + "': " + key);
      }
    }
  }

  std::string Config::get(const std::string& key) const {
    return provider_config_.at(key);
  }
  std::string Config::get_active_provider() const {
    return active_provider_;
  }
  
  std::vector<std::string> Config::required_fields_for(const std::string& provider) {
    if (provider == "DigitalOcean Spaces") {
      return {"token", "region", "bucket"};
    }
    // else if (provider == "AWS S3") {
    //   return {"access_key", "secret_key", "region", "bucket"};
    // }

    throw ConfigError("Unsupported provider: " + provider);
  }
}
