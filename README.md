# Cinema Seat Booking System

A console-based Cinema Seat Booking System developed in **C++17**. It allows users to view movie showtimes and seat availability, book multiple seats, cancel individual seats, view booking history, search bookings by ID, and view a sales summary.

## Features

- View available and booked seats for each movie and showtime
- Book one or multiple seats in a single booking
- Seat categories and pricing:
  - Economy (Rows A–C): Rs. 150
  - Premium (Rows D–G): Rs. 250
  - VIP (Rows H–J): Rs. 400
- Cancel a seat after confirming the booking ID
- View booking history
- Search a booking using its ID
- View seat sales and revenue summary
- Save bookings to a local text file and reload them when the program starts
- Validate menu choices and seat input

## Technologies and concepts

- C++17
- Classes and objects (OOP)
- Structures
- Arrays and vectors
- File handling (`ifstream`, `ofstream`)
- STL algorithms (`find_if`, `remove_if`, `count_if`)
- Input validation and string streams

## Project structure

```text
Cinema-Seat-Booking-System/
├── main.cpp
├── README.md
├── PROJECT_REPORT.md
├── CMakeLists.txt
├── .gitignore
├── bookings.txt.example
└── screenshots/
    └── README.md
```

## Requirements

- A C++ compiler that supports C++17 (GCC, Clang, or MSVC)
- A terminal or command prompt

## Compile and run

### Linux / macOS

```bash
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp -o cinema
./cinema
```

### Windows (MinGW)

```bash
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp -o cinema.exe
cinema.exe
```

### Using CMake

```bash
cmake -S . -B build
cmake --build build
```

Run the generated executable from the build output directory.

## How to use

1. Run the program.
2. Select an option from the main menu.
3. Choose a movie and showtime when prompted.
4. For booking, enter the customer name and seat labels separated by spaces, for example `C4 C5 D7`.
5. Keep the generated booking ID. It is required to confirm a cancellation.
6. Select `0` to exit.

## Data storage

The program stores booking records in `bookings.txt` in its current working directory. The file is created automatically when a booking is saved. Existing records are loaded when the program starts.

The repository includes `bookings.txt.example` as an example of the storage format. Rename/copy it to `bookings.txt` only if you want to test loading sample records. Do not commit real customer information.

Each record uses this format:

```text
booking_id|movie_index|show_index|row_index|column_index|customer_name
```

## Screenshots

Add genuine screenshots of the running program to the `screenshots/` folder. Suggested captures:

1. Main menu
2. Seat layout showing available and booked seats
3. Successful booking confirmation
4. Booking history
5. Sales summary

See `screenshots/README.md` for guidance.

## Limitations

- This is a local, single-user console application.
- It does not use a database or provide network-based booking.
- It does not process real payments.
- Movie names, showtimes, seat capacity, and prices are currently defined in the source code.
- The text-file storage is intended for a small academic project, not concurrent production use.

## Future improvements

- Add an administrator login and configurable movies/showtimes.
- Use a database such as SQLite or MySQL.
- Add booking receipts and customer contact details.
- Add a graphical user interface.
- Add automated unit tests.

## Academic submission

Update the project report with your actual name, enrollment number, course, faculty guide, and team details before submitting. Add only screenshots captured from your own program run.
