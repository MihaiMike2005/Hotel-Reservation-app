#ifndef ROOM_H
#define ROOM_H

#include <string>
#include <iostream>
#include <vector>
#include "Service.h"
using namespace std;

class Room {
protected:
    int number;
    double price;
    vector<Service> services;

public:
    Room(int n, double p) : number(n), price(p) {}
    virtual ~Room() {}

    int getNumber() const { return number; }
    double getPrice() const { return price; }

    const vector<Service>& getServices() const {return services; }

    virtual string getType() const = 0;  // polimorfism

    virtual void display() const {
        std::cout << "Room " << number << " | "
                  << getType() << " | Price: "
                  << price << " | Services: ";
        for (const auto& s : services)
            std::cout << s.getName() << " ";
        std::cout << "\n";
    }
    
};

#endif // ROOM_H
