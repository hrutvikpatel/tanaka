#include "service/tracked_folder_service.h"
#include "dao/tracked_folder_dao.h"
#include "utils/utils.h"
#include "utils/logger.h"
#include <filesystem>
#include <algorithm>

namespace tanaka::service
{
  using namespace tanaka::utils;

  TrackedFolderService::TrackedFolderService(std::shared_ptr<tanaka::dao::TrackedFolderDao> dao)
      : m_dao(std::move(dao)) {}

  OperationResult TrackedFolderService::addFolder(const std::string &path)
  {
    try
    {
      auto normalized = std::filesystem::weakly_canonical(path);
      if (isTracked(normalized))
      {
        return {false, "This folder is already being tracked."};
      }
      m_dao->addFolder(normalized.string());
      return {true, ""};
    }
    catch (const SQLite::Exception &e)
    {
      Logger::error("Database error while adding folder: {}", e.what());
      return {false, "Database error occurred while adding the folder."};
    }
  }

  OperationResult TrackedFolderService::removeFolder(const std::string &path)
  {
    try
    {
      auto normalized = std::filesystem::weakly_canonical(path);
      if (!m_dao->removeFolder(normalized.string()))
      {
        return {false, "Folder path does not exist: " + normalized.string()};
      }
      return {true, ""};
    }
    catch (const SQLite::Exception &e)
    {
      Logger::error("Database error while adding folder: {}", e.what());
      return {false, "Database error occurred while adding the folder."};
    }
  }

  ListFoldersResult TrackedFolderService::listFolders() const
  {
    try
    {
      auto folders = m_dao->getAllFolders();
      return {true, "", folders};
    }
    catch (const SQLite::Exception &e)
    {
      Logger::error("Database error while listing folders: {}", e.what());
      return {false, "Database error occurred while listing folders.", {}};
    }
  }

  bool TrackedFolderService::isTracked(const std::filesystem::path &newPath) const
  {
    for (const auto &tracked : m_dao->getAllFolders())
    {
      if (isSubPath(newPath, tracked))
      {
        return false;
      }

      if (newPath == std::filesystem::weakly_canonical(tracked))
      {
        return true;
      }
    }
    return false;
  }
}