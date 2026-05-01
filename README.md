# Hotel Reservation App

A console-based hotel management system written in C++, demonstrating object-oriented design with inheritance, polymorphism, and composition.

Built as a university OOP project.

## Features

- **Room management** — three room types (Standard, Deluxe, Suite) with per-type pricing and included services.
- **Reservations** — book a room for N nights, attach a client, calculate total cost including extras.
- **Service filtering** — search available rooms by required included services (WiFi, Breakfast, Pool, Spa).
- **Extra paid services** — add Spa, Airport pickup, or Gym Access to any reservation.
- **Client history** — look up all reservations for a given client by name.
- **File-based persistence** — rooms loaded from `data.txt` at startup.

## Class Design

```
Room (abstract)
 |-- StandardRoom
 |-- DeluxeRoom
 +-- SuiteRoom

Hotel        owns        std::vector<Room*>
             owns        std::vector<Reservation>

Reservation  has-a       Client      (composition)
             references  Room        (aggregation)
             owns        std::vector<Service>  (extras)
```

Key OOP decisions:

- `Room` is abstract via the pure virtual `getType()` — Standard/Deluxe/Suite must implement it. `display()` is virtual but provides a default.
- `Room`'s destructor is virtual because `Hotel` deletes rooms through a `Room*` pointer. Without virtual, derived destructors wouldn't run.
- `Reservation` uses **composition** for `Client` (a reservation owns its client snapshot) and **aggregation** for `Room` (the hotel owns rooms; the reservation just references one).

## Build & Run

### Using CMake (recommended, cross-platform)

mkdir build && cd build
cmake ..
cmake --build .
./hotel        # Linux/macOS
hotel.exe      # Windows

The program expects `data.txt` in the working directory.

## Data Format

`data.txt` defines the hotel's rooms, one per line:

```
Standard,101
Deluxe,201
Suite,301
```

Format: `<RoomType>,<RoomNumber>`.

## Project Structure

```
.
|-- main.cpp           Entry point and menu loop
|-- Hotel.h            Hotel aggregate, reservation flow
|-- Room.h             Abstract base class
|-- StandardRoom.h     Concrete room types
|-- DeluxeRoom.h
|-- SuiteRoom.h
|-- Reservation.h      Booking record
|-- Client.h           Client info
|-- Service.h          Included and extra services
|-- data.txt           Room definitions
+-- functionalities.md Feature notes
```

## Possible Improvements

- Replace raw `Room*` pointers with `std::unique_ptr<Room>` to make ownership explicit and eliminate the need for a manual destructor.
- Extract a `ConsoleUI` class — currently `Hotel` mixes domain logic with console I/O, violating SRP.
- Persist reservations to disk, not just rooms.
- Add input validation for the menu.

## Author

Mihai Stefanita — University of Craiova
