#include <gtest/gtest.h>
#include "config/config.h"
#include <unistd.h> // mkstemp, close, write
#include <stdexcept>
#include <string>

using namespace tanaka::config;

std::string write_temp_config(const std::string &content)
{
  char temp_filename[] = "/tmp/config_test_XXXXXX.toml";

  int fd = mkstemps(temp_filename, 5);
  if (fd == -1)
  {
    throw std::runtime_error("Failed to create temporary file");
  }

  if (write(fd, content.c_str(), content.size()) == -1)
  {
    close(fd);
    throw std::runtime_error("Failed to write to temporary file");
  }

  close(fd);

  return std::string(temp_filename);
}

TEST(ConfigTest, ValidConfigLoadsCorrectly)
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

  EXPECT_EQ(config.get_active_provider(), "DigitalOcean Spaces");
  EXPECT_EQ(config.get("token"), "abc123");
  EXPECT_EQ(config.get("region"), "nyc3");
  EXPECT_EQ(config.get("bucket"), "my-bucket");
}

TEST(ConfigTest, MissingProviderSectionThrows)
{
  std::string toml = R"(
    ["DigitalOcean Spaces"]
    token = "abc123"
    region = "nyc3"
    bucket = "my-bucket"
  )";

  std::string path = write_temp_config(toml);
  Config config;
  EXPECT_THROW(config.load(path), ConfigError);
}

TEST(ConfigTest, MissingActiveProviderFieldThrows)
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
  EXPECT_THROW(config.load(path), ConfigError);
}

TEST(ConfigTest, MissingRequiredFieldThrows)
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
  EXPECT_THROW(config.load(path), ConfigError);
}

TEST(ConfigTest, UnsupportedProviderThrows)
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
  EXPECT_THROW(config.load(path), ConfigError);
}