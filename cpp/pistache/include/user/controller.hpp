#pragma once
#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <pistache/router.h>

// Macro for const Pistache::Rest::Request &request
#define REQUEST const Pistache::Rest::Request &request
#define RESPONSE Pistache::Http::ResponseWriter response

class UserController {
public:
  UserController(Pistache::Rest::Router &router, std::string prefix)
      : _router(router), prefix(prefix) {}

  void setupRoutes();
private:
  Pistache::Rest::Router &_router;
  std::string prefix;

  void getUserById(REQUEST, RESPONSE);
};

#endif
