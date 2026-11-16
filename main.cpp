#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <limits>
using namespace std;

const int ROWS = 10;
const int COLS = 10;
const int MOVIES = 3;
const int SHOWS = 4;
const string FILE_NAME = "bookings.txt";

const string MOVIE_NAMES[MOVIES] = {
    "Interstellar", "Inception", "The Dark Knight"
};

const string SHOW_TIMES[SHOWS] = {
    "10:00 AM", "2:00 PM", "6:00 PM", "9:00 PM"
};

struct Booking {
    int id, movie, show, row, col;
    string customer;
};

class Seat {
public:
    bool booked = false;
    int bookingId = 0;
};

class CinemaSystem {
    Seat seats[MOVIES][SHOWS][ROWS][COLS];
    vector<Booking> bookings;
    int nextID = 1001;

    int priceOfRow(int r) const {
        if (r < 3) return 150;
        if (r < 7) return 250;
        return 400;
    }

    string categoryOfRow(int r) const {
        if (r < 3) return "Economy";
        if (r < 7) return "Premium";
        return "VIP";
    }

    bool isBooked(int m, int s, int r, int c) const {
        return seats[m][s][r][c].booked;
    }

    bool parseSeat(string seat, int& r, int& c) const {
        if (seat.size() < 2 || seat.size() > 3)
            return false;

        seat[0] = toupper(static_cast<unsigned char>(seat[0]));

        if (seat[0] < 'A' || seat[0] > 'J')
            return false;

        for (size_t i = 1; i < seat.size(); i++) {
            if (!isdigit(static_cast<unsigned char>(seat[i])))
                return false;
        }

        int col = stoi(seat.substr(1));

        if (col < 1 || col > COLS)
            return false;

        r = seat[0] - 'A';
        c = col - 1;
        return true;
    }

    string seatName(int r, int c) const {
        return string(1, char('A' + r)) + to_string(c + 1);
    }

    void placeOnGrid(const Booking& b) {
        seats[b.movie][b.show][b.row][b.col].booked = true;
        seats[b.movie][b.show][b.row][b.col].bookingId = b.id;
    }

    bool saveData() const {
        ofstream file(FILE_NAME);

        if (!file)
            return false;

        for (const auto& b : bookings) {
            file << b.id << '|'
                 << b.movie << '|'
                 << b.show << '|'
                 << b.row << '|'
                 << b.col << '|'
                 << b.customer << '\n';
        }

        return file.good();
    }

    void loadData() {
        ifstream file(FILE_NAME);
        string line;
        int maxID = 1000;

        while (getline(file, line)) {
            stringstream ss(line);
            string part;
            vector<string> fields;

            while (getline(ss, part, '|'))
                fields.push_back(part);

            if (fields.size() != 6)
                continue;

            try {
                Booking b;

                b.id = stoi(fields[0]);
                b.movie = stoi(fields[1]);
                b.show = stoi(fields[2]);
                b.row = stoi(fields[3]);
                b.col = stoi(fields[4]);
                b.customer = fields[5];

                if (b.id <= 0 ||
                    b.movie < 0 || b.movie >= MOVIES ||
                    b.show < 0 || b.show >= SHOWS ||
                    b.row < 0 || b.row >= ROWS ||
                    b.col < 0 || b.col >= COLS ||
                    b.customer.empty())
                    continue;

                bool duplicate = false;

                for (const auto& existing : bookings) {
                    if (existing.id == b.id ||
                        (existing.movie == b.movie &&
                         existing.show == b.show &&
                         existing.row == b.row &&
                         existing.col == b.col)) {
                        duplicate = true;
                        break;
                    }
                }

                if (duplicate)
                    continue;

                bookings.push_back(b);
                placeOnGrid(b);
                maxID = max(maxID, b.id);
            }
            catch (...) {
                continue;
            }
        }

        nextID = maxID + 1;
    }

    int readNumber(const string& prompt, int low, int high) const {
        string input;

        while (true) {
            cout << prompt;
            getline(cin, input);

            stringstream ss(input);
            int value;
            char extra;

            if (ss >> value && !(ss >> extra) &&
                value >= low && value <= high)
                return value;

            cout << "Invalid input. Try again.\n";
        }
    }

    void chooseMovie(int& movie, int& show) const {
        cout << "\n========== SELECT MOVIE ==========\n";

        for (int i = 0; i < MOVIES; i++)
            cout << i + 1 << ". " << MOVIE_NAMES[i] << '\n';

        movie = readNumber("Select movie: ", 1, MOVIES) - 1;

        cout << "\n========== SELECT SHOW ==========\n";

        for (int i = 0; i < SHOWS; i++)
            cout << i + 1 << ". " << SHOW_TIMES[i] << '\n';

        show = readNumber("Select showtime: ", 1, SHOWS) - 1;
    }

    void displaySeats(int m, int s) const {
        cout << "\nMovie: " << MOVIE_NAMES[m]
             << " | Show: " << SHOW_TIMES[s] << "\n\n";

        cout << "              SCREEN THIS WAY\n";
        cout << "       =================================\n\n";

        cout << "     ";

        for (int c = 0; c < COLS; c++)
            cout << setw(4) << c + 1;

        cout << "\n";

        for (int r = 0; r < ROWS; r++) {
            cout << "  " << char('A' + r) << "  ";

            for (int c = 0; c < COLS; c++) {
                cout << setw(4)
                     << (isBooked(m, s, r, c) ? "X" : "O");
            }

            cout << "   " << categoryOfRow(r)
                 << " (Rs." << priceOfRow(r) << ")\n";
        }

        cout << "\nO = Available | X = Booked\n";
    }

    void bookSeats() {
        int m, s;
        chooseMovie(m, s);
        displaySeats(m, s);

        string name;
        cout << "\nCustomer name: ";
        getline(cin, name);

        if (name.empty() || name.find('|') != string::npos) {
            cout << "Invalid customer name.\n";
            return;
        }

        cout << "Enter seats separated by spaces (e.g. C4 C5 D7):\n";

        string line;
        getline(cin, line);

        stringstream ss(line);
        string seat;
        vector<pair<int, int>> requested;

        while (ss >> seat) {
            int r, c;

            if (!parseSeat(seat, r, c)) {
                cout << "Invalid seat: " << seat << '\n';
                return;
            }

            for (const auto& p : requested) {
                if (p.first == r && p.second == c) {
                    cout << "Duplicate seat: " << seat << '\n';
                    return;
                }
            }

            if (isBooked(m, s, r, c)) {
                cout << "Seat " << seat << " is already booked.\n";
                return;
            }

            requested.push_back({r, c});
        }

        if (requested.empty()) {
            cout << "No seats entered.\n";
            return;
        }

        int id = nextID++;
        int total = 0;

        for (const auto& p : requested) {
            Booking b = {id, m, s, p.first, p.second, name};

            bookings.push_back(b);
            placeOnGrid(b);

            total += priceOfRow(p.first);
        }

        if (!saveData()) {
            for (const auto& p : requested) {
                seats[m][s][p.first][p.second] = Seat();
            }

            bookings.erase(
                remove_if(bookings.begin(), bookings.end(),
                    [id](const Booking& b) {
                        return b.id == id;
                    }),
                bookings.end()
            );

            nextID--;
            cout << "Booking failed. Could not save data.\n";
            return;
        }

        cout << "\n========== BOOKING CONFIRMED ==========\n";
        cout << "Booking ID: " << id << '\n';
        cout << "Customer: " << name << '\n';
        cout << "Movie: " << MOVIE_NAMES[m] << '\n';
        cout << "Show: " << SHOW_TIMES[s] << '\n';

        cout << "Seats: ";

        for (const auto& p : requested)
            cout << seatName(p.first, p.second) << " ";

        cout << "\nTotal seats: " << requested.size();
        cout << "\nTotal payable: Rs. " << total << '\n';
        cout << "=======================================\n";
    }

    void cancelSeat() {
        int m, s;
        chooseMovie(m, s);
        displaySeats(m, s);

        string seat;
        cout << "\nEnter seat to cancel: ";
        getline(cin, seat);

        int r, c;

        if (!parseSeat(seat, r, c)) {
            cout << "Invalid seat.\n";
            return;
        }

        if (!isBooked(m, s, r, c)) {
            cout << "Seat is not booked.\n";
            return;
        }

        int realID = seats[m][s][r][c].bookingId;

        auto it = find_if(bookings.begin(), bookings.end(),
            [&](const Booking& b) {
                return b.movie == m && b.show == s &&
                       b.row == r && b.col == c;
            });

        if (it == bookings.end()) {
            cout << "Booking record not found.\n";
            return;
        }

        cout << "Customer: " << it->customer << '\n';

        int id = readNumber(
            "Enter booking ID to confirm cancellation: ",
            1, numeric_limits<int>::max()
        );

        if (id != realID) {
            cout << "Incorrect booking ID. Cancellation denied.\n";
            return;
        }

        Booking cancelled = *it;
        int refund = priceOfRow(r);

        bookings.erase(it);
        seats[m][s][r][c] = Seat();

        if (!saveData()) {
            bookings.push_back(cancelled);
            placeOnGrid(cancelled);
            cout << "Cancellation failed. Could not save data.\n";
            return;
        }

        int remaining = count_if(
            bookings.begin(), bookings.end(),
            [realID](const Booking& b) {
                return b.id == realID;
            }
        );

        cout << "Seat " << seatName(r, c)
             << " cancelled successfully.\n";
        cout << "Refund amount: Rs. " << refund << '\n';
        cout << "Seats remaining under booking ID "
             << realID << ": " << remaining << '\n';
    }

    void bookedList() const {
        if (bookings.empty()) {
            cout << "\nNo bookings found.\n";
            return;
        }

        cout << "\n============== BOOKING HISTORY ==============\n";

        for (const auto& b : bookings) {
            cout << "ID: " << b.id
                 << " | " << b.customer
                 << " | " << MOVIE_NAMES[b.movie]
                 << " | " << SHOW_TIMES[b.show]
                 << " | Seat: " << seatName(b.row, b.col)
                 << " | Rs. " << priceOfRow(b.row) << '\n';
        }
    }

    void searchById() const {
        int id = readNumber(
            "Enter booking ID: ",
            1, numeric_limits<int>::max()
        );

        int total = 0;
        bool found = false;

        for (const auto& b : bookings) {
            if (b.id != id)
                continue;

            if (!found) {
                cout << "\nCustomer: " << b.customer
                     << "\nMovie: " << MOVIE_NAMES[b.movie]
                     << "\nShow: " << SHOW_TIMES[b.show]
                     << "\nSeats: ";

                found = true;
            }

            cout << seatName(b.row, b.col) << " ";
            total += priceOfRow(b.row);
        }

        if (found)
            cout << "\nTotal paid: Rs. " << total << '\n';
        else
            cout << "No booking found with that ID.\n";
    }

    void summary() const {
        int booked[3] = {0, 0, 0};
        int revenue[3] = {0, 0, 0};

        for (const auto& b : bookings) {
            int cat = b.row < 3 ? 0 : (b.row < 7 ? 1 : 2);
            booked[cat]++;
            revenue[cat] += priceOfRow(b.row);
        }

        const string names[] = {
            "Economy", "Premium", "VIP"
        };

        const int prices[] = {150, 250, 400};
        const int perShow[] = {
            3 * COLS, 4 * COLS, 3 * COLS
        };

        int screenings = MOVIES * SHOWS;

        cout << "\n====== SALES SUMMARY ======\n";

        cout << left << setw(12) << "Category"
             << setw(8) << "Price"
             << setw(10) << "Booked"
             << setw(12) << "Available"
             << "Revenue\n";

        int totalRevenue = 0;

        for (int i = 0; i < 3; i++) {
            int capacity = perShow[i] * screenings;

            cout << left << setw(12) << names[i]
                 << setw(8) << prices[i]
                 << setw(10) << booked[i]
                 << setw(12) << capacity - booked[i]
                 << revenue[i] << '\n';

            totalRevenue += revenue[i];
        }

        cout << "\nTotal seats booked: " << bookings.size();
        cout << "\nTotal revenue: Rs. " << totalRevenue << '\n';
    }

public:
    CinemaSystem() {
        loadData();
    }

    void run() {
        int choice;

        do {
            cout << "\n========================================\n";
            cout << "       CINEMA SEAT BOOKING SYSTEM\n";
            cout << "========================================\n";
            cout << "1. View seating arrangement\n";
            cout << "2. Book seat(s)\n";
            cout << "3. Cancel a seat\n";
            cout << "4. View booking history\n";
            cout << "5. Sales summary\n";
            cout << "6. Search booking by ID\n";
            cout << "0. Exit\n";
            cout << "========================================\n";

            choice = readNumber("Enter choice: ", 0, 6);

            switch (choice) {
                case 1: {
                    int m, s;
                    chooseMovie(m, s);
                    displaySeats(m, s);
                    break;
                }

                case 2:
                    bookSeats();
                    break;

                case 3:
                    cancelSeat();
                    break;

                case 4:
                    bookedList();
                    break;

                case 5:
                    summary();
                    break;

                case 6:
                    searchById();
                    break;

                case 0:
                    cout << "\nThank you for using Cinema Booking System!\n";
                    break;
            }

        } while (choice != 0);
    }
};

int main() {
    CinemaSystem cinema;
    cinema.run();
    return 0;
}