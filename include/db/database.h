#pragma once

#include <SQLiteCpp/SQLiteCpp.h>
#include <string>

namespace tanaka::db {
  class Database {
  public:
    explicit Database(const std::string& db_path);
    SQLite::Database& connection();

  private:
    SQLite::Database m_db;
  };
}