#include <catch2/catch_test_macros.hpp>
#include <db/database.h>
#include <unistd.h>  // mkstemp, close, unlink
#include <fstream>
#include <stdexcept>
#include <string>

using namespace tanaka::db;

std::string create_temp_db() {
  char temp_filename[] = "/tmp/tanaka_db_test_XXXXXX";
  int fd = mkstemps(temp_filename, 0);
  if (fd == -1) {
    throw std::runtime_error("Failed to create temporary db file");
  }
  close(fd);
  return std::string(temp_filename);
}

TEST_CASE("Database initializes and creates table") {
  std::string db_path = create_temp_db();
  Database db(db_path);
  auto& conn = db.connection();

  // Create table and insert
  conn.exec("CREATE TABLE IF NOT EXISTS test_table (id INTEGER PRIMARY KEY, name TEXT);");

  SQLite::Statement insert(conn, "INSERT INTO test_table (name) VALUES (?);");
  insert.bind(1, "hello");
  insert.exec();

  SQLite::Statement query(conn, "SELECT name FROM test_table WHERE id = 1;");
  REQUIRE(query.executeStep());
  REQUIRE(query.getColumn(0).getString() == "hello");

  std::filesystem::remove(db_path);  // Clean up temp file
}