#include <fmt/core.h>
#include <unordered_map>
#include <user/controller.hpp>

void UserController::setupRoutes() {
  using namespace Pistache::Rest;
  using Callback = void (UserController::*)(const Pistache::Rest::Request &,
                                            Pistache::Http::ResponseWriter);

  auto routeCompose = [this](std::string path) -> std::string {
    return fmt::format("{}/{}", this->prefix, path);
  };

  std::unordered_map<std::string, Callback> getRoutes{
      {routeCompose(":id"), &UserController::getUserById},
  };

  // For every routes in getRoutes
  for (auto [path, callback] : getRoutes) {
    Routes::Get(_router, path, Routes::bind(callback, this));
  }
}
void UserController::getUserById(const Pistache::Rest::Request &request,
                                 Pistache::Http::ResponseWriter response) {
  std::string id = request.param(":id").as<std::string>();
  response.send(Pistache::Http::Code::Ok, fmt::format("Hello, {}!", id));
}
