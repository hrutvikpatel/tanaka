#include <gtest/gtest.h>
#include "utils/utils.h"
#include <filesystem>

using namespace tanaka::utils;

TEST(IsSubPathTest, ReturnsTrueForValidSubpath) {
  std::filesystem::path parent = "/home/user/projects";
  std::filesystem::path child = "/home/user/projects/tanaka/data";

  EXPECT_TRUE(isSubPath(child, parent));
}

TEST(IsSubPathTest, ReturnsFalseForUnrelatedPaths) {
  std::filesystem::path parent = "/home/user/projects";
  std::filesystem::path child = "/home/other/folder";

  EXPECT_FALSE(isSubPath(child, parent));
}

TEST(IsSubPathTest, ReturnsFalseForSiblingPaths) {
  std::filesystem::path parent = "/home/user/projects";
  std::filesystem::path child = "/home/user/documents";

  EXPECT_FALSE(isSubPath(child, parent));
}

TEST(IsSubPathTest, ReturnsTrueWhenPathsAreSame) {
  std::filesystem::path parent = "/home/user/projects";
  std::filesystem::path child = "/home/user/projects";

  EXPECT_TRUE(isSubPath(child, parent));
}

TEST(IsSubPathTest, ResolvesSymbolicLinksAndRelativePaths) {
  std::filesystem::path tempDir = std::filesystem::temp_directory_path() / "tanaka_test";
  std::filesystem::create_directories(tempDir / "projects/data");

  std::filesystem::path parent = tempDir / "projects";
  std::filesystem::path child = tempDir / "projects/tanaka/../data";

  EXPECT_TRUE(isSubPath(child, parent));

  std::filesystem::remove_all(tempDir);
}