#ifndef SERVICE_H
#define SERVICE_H

#include <string>

class Service {
    std::string name;
    double cost;

public:
    Service(const std::string& n, double c) : name(n), cost(c) {}
    std::string getName() const { return name; }
    double getCost() const { return cost; }
};

#endif // SERVICE_H
