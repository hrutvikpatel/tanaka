#pragma

#include <filesystem>
#include <string>

namespace tanaka::utils {

  /**
   * @brief Checks if a given path is a subpath of another.
   *
   * This function determines whether the `child` path is located under the `parent` path
   * in the filesystem hierarchy. Both paths are normalized using `std::filesystem::weakly_canonical`
   * to resolve symbolic links, `.` and `..`, without requiring that all components exist.
   *
   * @param child The potential subpath.
   * @param parent The path to check against.
   * @return true if `child` is a subpath of `parent`, false otherwise.
   */
  bool isSubPath(const std::filesystem::path& child, const std::filesystem::path& parent);
}