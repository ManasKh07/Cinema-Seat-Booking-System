# Project Report: Cinema Seat Booking System

> **Before submission:** Replace all bracketed fields with your actual details. Remove any sections that your college format does not require.

## 1. Title

**Cinema Seat Booking System**

## 2. Student Details

- Student name: [Your name]
- Enrollment / roll number: [Your enrollment number]
- Course / branch: [Course and branch]
- Semester / section: [Semester and section]
- College: [College name]
- Faculty guide: [Guide name]
- Team members: [Names and enrollment numbers, if applicable]

## 3. Abstract

The Cinema Seat Booking System is a menu-driven C++ application designed to manage seat reservations for a small cinema. Users can select a movie and showtime, view the seating arrangement, book available seats, cancel a seat after booking-ID verification, view booking history, search for a booking, and view a sales summary. Booking information is stored in a text file so that records can be loaded when the application is run again.

## 4. Objectives

- Provide a simple interface for cinema seat selection and booking.
- Prevent booking seats that are already reserved.
- Calculate ticket prices according to seat category.
- Allow cancellation with booking-ID confirmation.
- Maintain booking records using file handling.
- Display booking and revenue summaries.

## 5. Software and Concepts Used

- Language: C++
- Standard: C++17
- Concepts: classes, objects, structures, arrays, vectors, file handling, string streams, input validation, and STL algorithms.
- Tools: Any C++17-compatible compiler and a text editor or IDE.

## 6. System Design

The `CinemaSystem` class manages the seating layout and booking records. The `Seat` class stores whether a seat is booked and its booking ID. The `Booking` structure stores the booking ID, movie index, show index, row, column, and customer name.

There are three movies and four showtimes. Each screening has a 10 × 10 seating arrangement. Rows A–C are Economy, rows D–G are Premium, and rows H–J are VIP.

## 7. Main Modules

1. **View seating arrangement:** Displays the seat grid for a selected movie and showtime.
2. **Book seats:** Validates the customer name and requested seats, calculates the total price, assigns a booking ID, and saves the records.
3. **Cancel a seat:** Checks the selected seat and requires the correct booking ID before cancellation.
4. **Booking history:** Displays saved booking entries.
5. **Sales summary:** Calculates booked seats and revenue for each seat category.
6. **Search booking:** Finds all seats associated with a booking ID.

## 8. File Handling

The application reads booking records from `bookings.txt` when it starts. After a successful booking or cancellation, it rewrites the file with the current booking records. The file uses pipe-separated fields:

`booking_id|movie_index|show_index|row_index|column_index|customer_name`

## 9. Compilation and Execution

Compile using:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp -o cinema
```

Run on Linux/macOS:

```bash
./cinema
```

Run on Windows:

```bash
cinema.exe
```

## 10. Testing

Record the results of tests you actually perform.

| Test case | Expected result | Actual result |
|---|---|---|
| View a movie's seats | Seat grid is displayed | [Fill in] |
| Book an available seat | Booking is confirmed and ID displayed | [Fill in] |
| Book an already booked seat | Booking is rejected | [Fill in] |
| Enter an invalid seat label | Input is rejected | [Fill in] |
| Cancel with correct booking ID | Seat is cancelled | [Fill in] |
| Cancel with incorrect booking ID | Cancellation is denied | [Fill in] |
| Restart after saving a booking | Saved booking is loaded | [Fill in] |
| Search an unknown booking ID | Not-found message is displayed | [Fill in] |

## 11. Screenshots

Insert your own screenshots here:

- Main menu
- Seat arrangement
- Booking confirmation
- Booking history
- Sales summary

## 12. Limitations

The application is a local, single-user console project. It does not connect to a payment gateway or remote database. Movie and show details are fixed in the source code. Text-file storage is not designed for simultaneous users.

## 13. Future Scope

The project can be extended with database integration, a graphical interface, administrator controls, configurable movie schedules, digital receipts, and automated tests.

## 14. Conclusion

The project demonstrates how C++ programming concepts can be combined to build a basic cinema reservation application. It uses object-oriented design, STL containers, input validation, and file handling to perform common booking operations and retain booking data between runs.
