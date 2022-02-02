#include <user/model.hpp>
#include <vector>

class UserService {
  public:
    bool addUser(User* user);
    bool removeUser(User* user);
    User getUser(const std::string& email);
    std::vector<User*> getUsers();
};
