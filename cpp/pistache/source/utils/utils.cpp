#include <utils/utils.hpp>

namespace Utils {
namespace Routes {

std::string routeCompose(const std::string &prefix, const std::string &path) {
  return fmt::format("{}/{}", prefix, path);
}

std::pair<std::string, std::string>
pathComposedExtraction(std::string pathComposed) {
  std::stringstream ss(pathComposed);
  std::string method, path;
  std::getline(ss, method, ' ');
  std::getline(ss, path, ' ');

  return std::make_pair(method, path);
}

} // namespace Routes
} // namespace Utils
