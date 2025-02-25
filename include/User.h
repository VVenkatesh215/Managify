#ifndef USER_H
#define USER_H

#include <string>
#include <fstream>
#include <chrono>
#include <ctime>

class User {
    std::string login_id;
    std::string password;

public:
    void signup(const std::string& filename);
    bool isLoginIdTaken(const std::string& filename, const std::string& id);
    bool login(const std::string& filename);
    void logLoginAttempt(bool success);
};

#endif // USER_H