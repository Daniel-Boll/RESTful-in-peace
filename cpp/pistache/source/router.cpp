#include <fmt/core.h>
#include <pistache/endpoint.h>
#include <router.hpp>
#include <user/controller.hpp>

Router::Router(int32_t port, int32_t threads = 2) {
  auto opts =
      Pistache::Http::Endpoint::options().threads(static_cast<int>(threads));

  auto addr = Pistache::Address(Pistache::Ipv4::any(), port);

  this->httpEndpoint = std::make_shared<Pistache::Http::Endpoint>(addr);
  this->httpEndpoint.get()->init(opts);
  this->setupRoutes();
}

void Router::setupRoutes() {
  using namespace Pistache::Rest;
  (new UserController(router, "/user"))->setupRoutes();

  Routes::Get(router, "/", Routes::bind(&Router::index, this));
}

void Router::index(const Pistache::Rest::Request &,
                   Pistache::Http::ResponseWriter response) {
  response.send(Pistache::Http::Code::Ok, "Server is running.");
}

void Router::start() {
  std::cout << "Server running" << std::endl;
  this->httpEndpoint.get()->setHandler(router.handler());
  this->httpEndpoint.get()->serve();
}
