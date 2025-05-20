#include "db/database.h"

namespace tanaka::db {
  Database::Database(const std::string& db_path)
    : m_db(db_path, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE) {
  }

  SQLite::Database& Database::connection() {
    return m_db;
  }
}