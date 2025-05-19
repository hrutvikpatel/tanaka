#include <catch2/catch_test_macros.hpp>
#include "config/config.h"
#include <fstream>
#include <unistd.h> // mkstemp, close, unlink
#include <stdexcept>
#include <string>

using namespace tanaka::config;

std::string write_temp_config(const std::string &content)
{
  char temp_filename[] = "/tmp/config_test_XXXXXX.toml";

  // mkstemps supports custom suffix like .toml (note: 5 chars = ".toml")
  int fd = mkstemps(temp_filename, 5);
  if (fd == -1)
  {
    throw std::runtime_error("Failed to create temporary file");
  }

  // Write content using file descriptor
  if (write(fd, content.c_str(), content.size()) == -1)
  {
    close(fd);
    throw std::runtime_error("Failed to write to temporary file");
  }

  // Close the file descriptor so that std::ifstream/Config can read it
  close(fd);

  return std::string(temp_filename);
}

TEST_CASE("Valid config with DigitalOcean Spaces loads corretly")
{
  std::string toml = R"(
    [provider]
    active = "DigitalOcean Spaces"

    ["DigitalOcean Spaces"]
    token = "abc123"
    region = "nyc3"
    bucket = "my-bucket"
  )";

  std::string path = write_temp_config(toml);
  Config config;
  config.load(path);

  REQUIRE(config.get_active_provider() == "DigitalOcean Spaces");
  REQUIRE(config.get("token") == "abc123");
  REQUIRE(config.get("region") == "nyc3");
  REQUIRE(config.get("bucket") == "my-bucket");
}

TEST_CASE("Missing [provider] section throws")
{
  std::string toml = R"(
    ["DigitalOcean Spaces"]
    token = "abc123"
    region = "nyc3"
    bucket = "my-bucket"
  )";

  std::string path = write_temp_config(toml);
  Config config;
  REQUIRE_THROWS_AS(config.load(path), ConfigError);
}

TEST_CASE("Missing active provider field throws")
{
  std::string toml = R"(
    [provider]
    # active = "DigitalOcean Spaces"

    ["DigitalOcean Spaces"]
    token = "abc123"
    region = "nyc3"
    bucket = "my-bucket"
  )";

  std::string path = write_temp_config(toml);
  Config config;
  REQUIRE_THROWS_AS(config.load(path), ConfigError);
}

TEST_CASE("Missing required field throws")
{
  std::string toml = R"(
    [provider]
    active = "DigitalOcean Spaces"

    ["DigitalOcean Spaces"]
    token = "abc123"
    region = "nyc3"
    # bucket is missing
  )";

  std::string path = write_temp_config(toml);
  Config config;
  REQUIRE_THROWS_AS(config.load(path), ConfigError);
}

TEST_CASE("Unsupported provider throws")
{
  std::string toml = R"(
    [provider]
    active = "AWS S3"

    ["AWS S3"]
    access_key = "AKIA"
    secret_key = "SECRET"
    region = "us-east-1"
    bucket = "my-bucket"
  )";

  std::string path = write_temp_config(toml);
  Config config;
  REQUIRE_THROWS_AS(config.load(path), ConfigError);
}
