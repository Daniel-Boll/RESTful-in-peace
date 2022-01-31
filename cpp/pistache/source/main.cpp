#include <fmt/core.h>
#include <iostream>
#include <router.hpp>

int main(int argc, char *argv[]) {
  Router *router = new Router(8081, 4);

  router->start();
}
