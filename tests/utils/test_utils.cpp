#include <catch2/catch_test_macros.hpp>
#include "utils/utils.h"

using namespace tanaka::utils;

TEST_CASE("isSubPath returns true for valid subpath")
{
  std::filesystem::path parent = "/home/user/projects";
  std::filesystem::path child = "/home/user/projects/tanaka/data";

  REQUIRE(isSubPath(child, parent));
}

TEST_CASE("isSubPath returns false for unrelated paths")
{
  std::filesystem::path parent = "/home/user/projects";
  std::filesystem::path child = "/home/other/folder";

  REQUIRE_FALSE(isSubPath(child, parent));
}

TEST_CASE("isSubPath returns false for sibling paths")
{
  std::filesystem::path parent = "/home/user/projects";
  std::filesystem::path child = "/home/user/documents";

  REQUIRE_FALSE(isSubPath(child, parent));
}

TEST_CASE("isSubPath returns true when paths are the same")
{
  std::filesystem::path parent = "/home/user/projects";
  std::filesystem::path child = "/home/user/projects";

  REQUIRE(isSubPath(child, parent));
}

TEST_CASE("isSubPath resolves symbolic links and relative paths")
{
  std::filesystem::path tempDir = std::filesystem::temp_directory_path() / "tanaka_test";
  std::filesystem::create_directories(tempDir / "projects/data");

  std::filesystem::path parent = tempDir / "projects";
  std::filesystem::path child = tempDir / "projects/tanaka/../data";

  REQUIRE(tanaka::utils::isSubPath(child, parent));

  std::filesystem::remove_all(tempDir);
}