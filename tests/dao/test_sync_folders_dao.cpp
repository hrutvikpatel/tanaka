#include <catch2/catch_test_macros.hpp>
#include "dao/sync_folder_dao.h"
#include <SQLiteCpp/SQLiteCpp.h>
#include <vector>
#include <string>
#include <algorithm>

using namespace tanaka::dao;

TEST_CASE("SyncFolderDao can add and list folders")
{
  SQLite::Database db(":memory:", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
  SyncFolderDao dao(db);

  dao.addFolder("/Users/test/Documents");
  dao.addFolder("/Users/test/Downloads");

  SQLite::Statement query(db, "SELECT path FROM sync_folders ORDER BY id ASC");

  std::vector<std::string> paths;
  while (query.executeStep())
  {
    paths.push_back(query.getColumn(0).getString());
  }

  REQUIRE(paths.size() == 2);
  REQUIRE(paths[0] == "/Users/test/Documents");
  REQUIRE(paths[1] == "/Users/test/Downloads");
}

TEST_CASE("SyncFolderDao prevents duplicate entries")
{
  SQLite::Database db(":memory:", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
  SyncFolderDao dao(db);

  dao.addFolder("/Users/test/Documents");
  dao.addFolder("/Users/test/Documents"); // Duplicate

  SQLite::Statement query(db, "SELECT COUNT(*) FROM sync_folders WHERE path = ?");
  query.bind(1, "/Users/test/Documents");
  REQUIRE(query.executeStep());
  REQUIRE(query.getColumn(0).getInt() == 1);
}

TEST_CASE("SyncFolderDao can delete existing folder")
{
  SQLite::Database db(":memory:", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
  SyncFolderDao dao(db);

  dao.addFolder("/Users/test/Documents");
  REQUIRE(dao.removeFolder("/Users/test/Documents") == true);

  SQLite::Statement query(db, "SELECT COUNT(*) FROM sync_folders WHERE path = ?");
  query.bind(1, "/Users/test/Documents");
  REQUIRE(query.executeStep());
  REQUIRE(query.getColumn(0).getInt() == 0); // Should be deleted
}

TEST_CASE("SyncFolderDao returns false when deleting non-existent folder")
{
  SQLite::Database db(":memory:", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
  SyncFolderDao dao(db);

  REQUIRE(dao.removeFolder("/Users/test/Missing") == false);

  // Optional: ensure table is still empty
  SQLite::Statement query(db, "SELECT COUNT(*) FROM sync_folders");
  REQUIRE(query.executeStep());
  REQUIRE(query.getColumn(0).getInt() == 0);
}