#ifndef ADMIN_H
#define ADMIN_H

#include <string>

class Admin {
public:
    bool login(const std::string& username, const std::string& password);
    bool displayLoginPrompt();

private:
    static const std::string default_name;
    static const std::string default_pwd;
};

#endif // Admin.h

