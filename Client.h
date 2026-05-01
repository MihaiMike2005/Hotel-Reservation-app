#ifndef CLIENT_H
#define CLIENT_H

#include <string>

class Client {

   std::string name;
   std::string phone;

public:
    Client(const std::string& n, const std::string& p) : name(n), phone(p) {}

    std::string getName() const { return name; }
};

#endif // CLIENT_H
