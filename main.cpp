#include <iostream>
#include <fstream>
#include <sstream>
#include "Hotel.h"
#include "StandardRoom.h"
#include "DeluxeRoom.h"
#include "SuiteRoom.h"

void loadRooms(const std::string& file, Hotel& hotel) {
    std::ifstream fin(file);
    std::string line;

    while (getline(fin, line)) {
        std::stringstream ss(line);
        std::string type, nr;

        getline(ss, type, ',');
        getline(ss, nr);

        int number = std::stoi(nr);

        if (type == "Standard")
            hotel.addRoom(new StandardRoom(number));
        else if (type == "Deluxe")
            hotel.addRoom(new DeluxeRoom(number));
        else if (type == "Suite")
            hotel.addRoom(new SuiteRoom(number));
    }
}

int main() {
    Hotel hotel;
    loadRooms("data.txt", hotel);

    int opt;
    do {
        std::cout << "\n1. Show rooms\n"
            << "2. Make reservation\n"
            << "3. Show all reservations\n"
            << "4. Client history\n"
            << "0. Exit\nChoice: ";
        std::cin >> opt;

        switch (opt) {
        case 1: hotel.showRooms(); break;
        case 2: hotel.createReservationInteractive(); break;
        case 3: hotel.showAllReservations(); break;
        case 4: {
            std::cin.ignore();
            std::string name;
            std::cout << "Client name: ";
            getline(std::cin, name);
            hotel.showClientHistory(name);
            break;
        }
        case 0: std::cout << "Goodbye!\n"; break;
        default: std::cout << "Invalid option!\n";
        }
    } while (opt != 0);

    return 0;
}
