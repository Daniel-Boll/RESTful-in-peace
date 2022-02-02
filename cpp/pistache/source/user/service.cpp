#include <iostream>
#include <thread>
#include <user/service.hpp>

bool UserService::addUser(User *user) {
  std::cout << "User created" << std::endl;

  return true;
}

bool UserService::removeUser(User *user) {
  std::cout << "User removed" << std::endl;

  return true;
}

User UserService::getUser(const std::string &email) {
  std::cout << "User retrieved" << std::endl;

  // Sleep for a while to simulate a long running operation
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));

  User user = {"John", "123", "john.email@email.com", "123456789", "user"};

  return user;
}
