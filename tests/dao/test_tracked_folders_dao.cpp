#include <gtest/gtest.h>
#include "dao/tracked_folder_dao.h"
#include <SQLiteCpp/SQLiteCpp.h>
#include <vector>
#include <string>
#include <algorithm>

using namespace tanaka::dao;

class TrackedFolderDaoTest : public ::testing::Test {
protected:
  SQLite::Database db{":memory:", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE};
  TrackedFolderDao dao{db};

  std::vector<std::string> getAllPaths() {
    SQLite::Statement query(db, "SELECT path FROM tracked_folders ORDER BY id ASC");
    std::vector<std::string> paths;
    while (query.executeStep()) {
      paths.push_back(query.getColumn(0).getString());
    }
    return paths;
  }

  int countPaths(const std::string& path) {
    SQLite::Statement query(db, "SELECT COUNT(*) FROM tracked_folders WHERE path = ?");
    query.bind(1, path);
    query.executeStep();
    return query.getColumn(0).getInt();
  }

  int countAll() {
    SQLite::Statement query(db, "SELECT COUNT(*) FROM tracked_folders");
    query.executeStep();
    return query.getColumn(0).getInt();
  }
};

TEST_F(TrackedFolderDaoTest, CanAddAndListFolders) {
  dao.addFolder("/Users/test/Documents");
  dao.addFolder("/Users/test/Downloads");

  auto paths = getAllPaths();

  EXPECT_EQ(paths.size(), 2);
  EXPECT_EQ(paths[0], "/Users/test/Documents");
  EXPECT_EQ(paths[1], "/Users/test/Downloads");
}

TEST_F(TrackedFolderDaoTest, PreventsDuplicateEntries) {
  dao.addFolder("/Users/test/Documents");
  dao.addFolder("/Users/test/Documents");  // duplicate

  EXPECT_EQ(countPaths("/Users/test/Documents"), 1);
}

TEST_F(TrackedFolderDaoTest, CanDeleteExistingFolder) {
  dao.addFolder("/Users/test/Documents");

  EXPECT_TRUE(dao.removeFolder("/Users/test/Documents"));

  EXPECT_EQ(countPaths("/Users/test/Documents"), 0);
}

TEST_F(TrackedFolderDaoTest, ReturnsFalseWhenDeletingNonExistentFolder) {
  EXPECT_FALSE(dao.removeFolder("/Users/test/Missing"));

  // Optional: ensure table is still empty
  EXPECT_EQ(countAll(), 0);
}