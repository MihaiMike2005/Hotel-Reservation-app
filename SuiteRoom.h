#pragma once
#ifndef SUITEROOM_H
#define SUITEROOM_H

#include "Room.h"

class SuiteRoom : public Room {
	public:
		SuiteRoom(int n) : Room(n, 450) {
			services.emplace_back("WiFi", 0);
			services.emplace_back("Breakfast", 0);
			services.emplace_back("Pool access", 0);
			services.emplace_back("Spa", 0);
		}
		std::string getType() const override { return "Suite"; }
};

#endif // SUITEROOM_H
