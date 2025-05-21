#include "dao/sync_folder_dao.h"

namespace tanaka::dao
{
  SyncFolderDao::SyncFolderDao(SQLite::Database &db)
      : m_db(db)
  {
    m_db.exec(R"(
      CREATE TABLE IF NOT EXISTS sync_folders (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        path TEXT NOT NULL UNIQUE
      );
    )");
  }

  void SyncFolderDao::addFolder(const std::string &path)
  {
    SQLite::Statement query(m_db, "INSERT OR IGNORE INTO sync_folders (path) VALUES (?);");
    query.bind(1, path);
    query.exec();
  }

  bool SyncFolderDao::removeFolder(const std::string &path)
  {
    SQLite::Statement query(m_db, "DELETE FROM sync_folders WHERE path = ?;");
    query.bind(1, path);
    int rowsAffected = query.exec();
    return rowsAffected > 0;
  }

  std::vector<std::string> SyncFolderDao::getAllFolders()
  {
    std::vector<std::string> result;
    SQLite::Statement query(m_db, "SELECT path FROM sync_folders ORDER BY path ASC;");
    while (query.executeStep())
    {
      result.push_back(query.getColumn(0).getString());
    }
    return result;
  }
}