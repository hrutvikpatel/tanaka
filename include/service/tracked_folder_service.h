#pragma once

#include <string>
#include <vector>
#include <memory>
#include <filesystem>

namespace tanaka::dao
{
  class TrackedFolderDao;
}

namespace tanaka::service
{

  struct OperationResult
  {
    bool success;
    std::string message;
  };

  struct ListFoldersResult
  {
    bool success;
    std::string message;
    std::vector<std::string> folders;
  };

  /**
   * @class TrackedFolderService
   * @brief Service layer for managing tracked folders used for backup.
   *
   * This class provides a higher-level interface for adding, removing,
   * checking, and listing folders that are being tracked for backup,
   * delegating data persistence to TrackedFolderDao.
   */
  class TrackedFolderService
  {
  public:
    /**
     * @brief Constructs the service with a shared DAO instance.
     * @param dao Shared pointer to a TrackedFolderDao.
     */
    explicit TrackedFolderService(std::shared_ptr<tanaka::dao::TrackedFolderDao> dao);

    /**
     * @brief Adds a folder to the tracked list if it is not already tracked or a subfolder of another tracked folder.
     * @param path The folder path to track.
     * @return True if the folder was successfully added, false otherwise.
     */
    OperationResult addFolder(const std::string &path);

    /**
     * @brief Removes a folder from the tracked list.
     * @param path The folder path to remove.
     * @return True if the folder was removed, false if it was not found.
     */
    OperationResult removeFolder(const std::string &path);

    /**
     * @brief Lists all currently tracked folders.
     * @return A vector of strings containing the tracked folder paths.
     */
    ListFoldersResult listFolders() const;

    /**
     * @brief Checks if a given path is already tracked.
     * @param path The path to check.
     * @return True if the path is tracked, false otherwise.
     */
    bool isTracked(const std::filesystem::path &newPath) const;

  private:
    std::shared_ptr<tanaka::dao::TrackedFolderDao> m_dao;
  };
}