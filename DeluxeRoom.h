#pragma once
#ifndef DELUXEROOM_H
#define DELUXEROOM_H
#include "Room.h"

class DeluxeRoom : public Room {
public:
	DeluxeRoom(int n) : Room(n, 250) {
	    services.emplace_back("WiFi", 0);
		services.emplace_back("Breakfast", 0);
		services.emplace_back("Pool access", 0);
	}

	std::string getType() const override { return "Deluxe"; }
};

#endif // DELUXEROOM_H
