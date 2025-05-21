#pragma once

#include <SQLiteCpp/SQLiteCpp.h>
#include <string>
#include <vector>

namespace tanaka::dao
{
  class TrackedFolderDao
  {
  public:
    explicit TrackedFolderDao(SQLite::Database &db);

    void addFolder(const std::string &path);
    bool removeFolder(const std::string &path);
    std::vector<std::string> getAllFolders();

  private:
    SQLite::Database &m_db;
  };
}