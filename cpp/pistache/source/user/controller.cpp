#include <cstdint>
#include <fmt/core.h>
#include <future>
#include <nlohmann/json.hpp>
#include <pistache/http_defs.h>
#include <sstream>
#include <user/controller.hpp>
#include <utils/utils.hpp>

void UserController::setupRoutes() {
  using namespace Pistache::Rest;
  using Callback = void (UserController::*)(const Pistache::Rest::Request &,
                                            Pistache::Http::ResponseWriter);

  std::unordered_map<std::string, Callback> routes{
      {"get :id", &UserController::getUserById},
  };

  for (auto [pathComposed, callback] : routes) {
    auto [method, path] = Utils::Routes::pathComposedExtraction(pathComposed);
    auto route = Utils::Routes::routeCompose(this->prefix, path);
    _router.addRoute(Utils::Routes::mapMethods[method], route,
                     Routes::bind(callback, this));
  }
}

void UserController::getUserById(const Pistache::Rest::Request &request,
                                 Pistache::Http::ResponseWriter response) {
  std::string id = request.param(":id").as<std::string>();

  std::future<User> result = std::async(std::launch::async, [&]() -> User {
    return this->service->getUser(id);
  });

  auto user = result.get();

  fmt::print("{}\n", user.email);

  response.send(Pistache::Http::Code::Ok, fmt::format("Hello, {}! <-", user.email));
}
