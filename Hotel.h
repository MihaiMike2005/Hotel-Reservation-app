#ifndef HOTEL_H
#define HOTEL_H

#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include "Reservation.h"

class Hotel {
private:
    std::vector<Room*> rooms;
    std::vector<Reservation> reservations;

    // Extra paid services menu
    std::vector<Service> extraMenu{
        Service("Spa", 50),
        Service("Airport pickup", 70),
        Service("Gym Access", 15)
    };

    bool hasIncludedService(Room* room, const std::string& serviceName) const {
        for (const auto& s : room->getServices()) {
            if (s.getName() == serviceName) return true;
        }
        return false;
    }

public:
    ~Hotel() {
        for (auto r : rooms)
            delete r;
    }

    void addRoom(Room* r) { rooms.push_back(r); }

    Room* findRoom(int number) const {
        for (auto r : rooms)
            if (r->getNumber() == number)
                return r;
        return nullptr;
    }

    bool isRoomAvailable(Room* room) const {
        for (const auto& rez : reservations)
            if (rez.getRoom()->getNumber() == room->getNumber())
                return false;
        return true;
    }

    void showRooms() const {
        for (auto r : rooms)
            r->display();
    }

    void showAvailableRooms() const {
        bool any = false;

        for (auto r : rooms) {
            if (isRoomAvailable(r)) {
                r->display();
                any = true;
            }
        }

        if (!any)
            std::cout << "Currently no available rooms.\n";
    }

    void showRoomsByIncludedServices(const std::vector<std::string>& required) const {
        bool any = false;

        for (auto r : rooms) {
            if (!isRoomAvailable(r)) continue;

            bool ok = true;
            for (const auto& req : required) {
                if (!hasIncludedService(r, req)) {
                    ok = false;
                    break;
                }
            }

            if (ok) {
                r->display();
                any = true;
            }
        }

        if (!any)
            std::cout << "No available rooms match the requested included services.\n";
    }

    void makeReservation(const Reservation& res) {
        if (isRoomAvailable(res.getRoom())) {
            reservations.push_back(res);
            std::cout << "Reservation successful!\n";
        }
        else {
            std::cout << "Room " << res.getRoom()->getNumber()
                << " is already reserved!\n";
        }
    }

    void showAllReservations() const {
        if (reservations.empty()) {
            std::cout << "Currently no reservations.\n";
            return;
        }

        for (const auto& r : reservations)
            r.display();
    }

    void showClientHistory(const std::string& name) const {
        if (reservations.empty()) {
            std::cout << "Currently no reservations.\n";
            return;
        }

        bool found = false;
        for (const auto& r : reservations) {
            if (r.getClient().getName() == name) {
                r.display();
                found = true;
            }
        }

        if (!found)
            std::cout << "No reservations found for this client.\n";
    }

    // Full reservation flow: included-services filtering + extra services + availability checks
    void createReservationInteractive() {
        std::cin.ignore();
        std::string name, phone;
        int nights, roomNr;

        std::cout << "Client name: ";
        getline(std::cin, name);
        std::cout << "Phone: ";
        getline(std::cin, phone);
        std::cout << "Nights: ";
        std::cin >> nights;

        // -------- Included services filter --------
        std::cin.ignore();
        std::cout << "\nIncluded services you want (numbers separated by space).\n";
        std::cout << "Press Enter for NO FILTER.\n";
        std::cout << "1. WiFi\n2. Breakfast\n3. Pool\n4. Spa\n";
        std::cout << "Choice: ";

        std::string line;
        getline(std::cin, line);

        std::vector<std::string> required;

        if (line.empty()) {
            std::cout << "\nAvailable rooms (no filtering):\n";
            showAvailableRooms();
        }
        else {
            std::stringstream ss(line);
            int x;
            while (ss >> x) {
                if (x == 1) required.push_back("WiFi");
                else if (x == 2) required.push_back("Breakfast");
                else if (x == 3) required.push_back("Pool");
                else if (x == 4) required.push_back("Spa");
            }

            std::cout << "\nAvailable rooms matching your included services:\n";
            showRoomsByIncludedServices(required);
        }

        // -------- Choose room --------
        std::cout << "Room number: ";
        std::cin >> roomNr;

        Room* room = findRoom(roomNr);
        if (!room) {
            std::cout << "Invalid room number!\n";
            return;
        }
        if (!isRoomAvailable(room)) {
            std::cout << "Room is already reserved!\n";
            return;
        }

        // If filtered, ensure selected room satisfies requirements
        for (const auto& req : required) {
            if (!hasIncludedService(room, req)) {
                std::cout << "Selected room does NOT satisfy requested included services!\n";
                return;
            }
        }

        Reservation res(Client(name, phone), room, nights);

        // -------- Extra paid services --------
        std::cout << "\nAvailable extra services:\n";
        for (size_t i = 0; i < extraMenu.size(); ++i)
            std::cout << i + 1 << ". " << extraMenu[i].getName()
            << " ($" << extraMenu[i].getCost() << ")\n";

        std::cin.ignore();
        std::cout << "\nClient's choice (enter numbers separated by space and press Enter):\n";
        getline(std::cin, line);

        std::stringstream ss2(line);
        int x;
        while (ss2 >> x) {
            if (x >= 1 && x <= (int)extraMenu.size())
                res.addExtraService(extraMenu[x - 1]);
        }

        makeReservation(res);
    }
};

#endif
