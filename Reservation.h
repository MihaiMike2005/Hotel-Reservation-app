#pragma once
#ifndef RESERVATION_H
#define RESERVATION_H

#include "Room.h"
#include "Client.h"
#include "Service.h"
#include <vector>

class Reservation {
	Client client;
	Room* room;
	int nights;
	std::vector<Service> extraServices;

public:
	Reservation(const Client& c, Room* r, int n) : client(c), room(r), nights(n) {}

	const Client& getClient() const { return client; }
	Room* getRoom() const { return room; }
	int getNights() const { return nights; }

	void addExtraService(const Service& s) {
		extraServices.push_back(s);
	}
	double total() const{
		double sum = room->getPrice() * nights;
		for(const auto& s : extraServices)
			sum += s.getCost();
		return sum;
	}

	void display() const{
		std::cout<< "Client: " << client.getName()
		         << " | Room: " << room->getNumber()
		         << " (" << room->getType() << ")"
			     << " | Nights: " << nights <<"\n";

		if(!extraServices.empty()){
			std::cout << "  Extra Services: ";
			for(auto& s : extraServices)
				std::cout << s.getName() << " ";
			std::cout << "\n";
		}
		std::cout << "  Total: " << total() << "\n";
	}
};

#endif // RESERVATION_H
