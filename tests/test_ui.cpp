#include <catch2/catch_test_macros.hpp>
#include "ui.h"
#include <sstream>
#include <iostream>
#include <vector>
#include <cstring>

using namespace tanaka::ui;

TEST_CASE("UI run executes 'configure' command", "[ui][run]")
{
  // Simulate CLI args: program name + configure
  const char *argv0 = "test_ui";
  const char *argv1 = "configure";
  int argc = 2;

  // Simulate user input (invalid selection to test fallback)
  std::istringstream input("invalid_choice\n");
  std::ostringstream output;

  // Backup original std streams
  auto cin_buf = std::cin.rdbuf();
  auto cout_buf = std::cout.rdbuf();

  // Redirect cin/cout
  std::cin.rdbuf(input.rdbuf());
  std::cout.rdbuf(output.rdbuf());

  // Call UI::run
  UI::run(argc, const_cast<char **>(std::array<const char *, 2>{argv0, argv1}.data()));

  // Restore original std streams
  std::cin.rdbuf(cin_buf);
  std::cout.rdbuf(cout_buf);

  // Validate output
  std::string out = output.str();
  REQUIRE(out.find("Available providers:") != std::string::npos);
  REQUIRE(out.find("Invalid selection.") != std::string::npos);
}