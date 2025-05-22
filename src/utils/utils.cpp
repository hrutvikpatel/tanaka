#include "utils/utils.h"

namespace tanaka::utils {
  bool isSubPath(const std::filesystem::path& child, const std::filesystem::path& parent) {
    auto childAbs = std::filesystem::weakly_canonical(child);
    auto parentAbs = std::filesystem::weakly_canonical(parent);
    return std::mismatch(parentAbs.begin(), parentAbs.end(), childAbs.begin()).first == parentAbs.end();
  }
}