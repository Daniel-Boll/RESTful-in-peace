#ifndef ROUTER_HPP
#define ROUTER_HPP

#include <pistache/endpoint.h>
#include <pistache/http.h>
#include <pistache/router.h>
#include <user/controller.hpp>

class Router {
private:
  using Lock = std::mutex;
  using Guard = std::lock_guard<Lock>;

  std::shared_ptr<Pistache::Http::Endpoint> httpEndpoint;
  Pistache::Rest::Router router;
public:
  Router(int32_t port, int32_t threads);

  void setupRoutes();

  void index(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response);

  void start();
};

#endif
