#pragma once

#include <SQLiteCpp/SQLiteCpp.h>
#include <string>
#include <vector>

namespace tanaka::dao
{
  class SyncFolderDao
  {
  public:
    explicit SyncFolderDao(SQLite::Database &db);

    void addFolder(const std::string &path);
    bool removeFolder(const std::string &path);
    std::vector<std::string> getAllFolders();

  private:
    SQLite::Database &m_db;
  };
}