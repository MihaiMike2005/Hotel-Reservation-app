#pragma once
#ifndef STANDARDROOM_H
#define STANDARDROOM_H

#include "Room.h"

class StandardRoom : public Room {
public:
	StandardRoom(int n) : Room(n, 120) {
		services.emplace_back("WiFi", 0);
		services.emplace_back("Breakfast", 0);
	}
	std::string getType() const override { return "Standard"; }
};
#endif // STANDARDROOM_H
