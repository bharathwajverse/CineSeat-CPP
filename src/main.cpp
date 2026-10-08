/**
 * CineSeat — Smart Movie Ticket Booking & Waitlist System
 * Academic C++ DSA Mini Project with MySQL Integration
 * Standard: C++17
 *
 * Syllabus Elements Covered:
 * - 2D Array: seats[5][6] (0 = available, 1 = booked)
 * - Structures: struct Booking
 * - Strings & Direct Math calculations
 * - STL Containers: vector, queue, stack
 * - Searching: Linear Search by customer name
 * - Sorting: std::sort by customer name
 * - MySQL Integration: connectDatabase, loadBookings, saveBooking, deleteBooking
 * - Clean menu-driven console interface with robust input validation
 */

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <string>
#include <algorithm>
#include <iomanip>
#include <limits>
#include "database.h"

using namespace std;

// Fixed Cinema Layout Constants
const int ROWS = 5;
const int COLS = 6;
const string FIXED_MOVIE = "Interstellar";

// Base ticket pricing tiers
const double FRONT_ROW_PRICE = 150.00; // Rows 0-1
const double MID_ROW_PRICE   = 200.00; // Rows 2-3
const double BACK_ROW_PRICE  = 250.00; // Row 4 (VIP/Recliner)

// ==========================================
// 1. Global State & Data Structures
// ==========================================

// Global state designed for academic clarity & simplicity
int seats[ROWS][COLS] = {0}; // 0 = Available, 1 = Booked
vector<Booking> bookings;     // Active bookings
queue<string> waitlist;       // FIFO Waiting queue when theater is full
stack<Booking> undoStack;     // LIFO Stack for undoing last booking
int nextBookingId = 101;      // Auto-incrementing identifier

// ==========================================
// 2. Helper & Validation Functions
// ==========================================

bool isSeatValid(int row, int col) {
    return (row >= 0 && row < ROWS && col >= 0 && col < COLS);
}

bool isSeatAvailable(int row, int col) {
    if (!isSeatValid(row, col)) return false;
    return (seats[row][col] == 0);
}

bool isTheaterFull() {
    for (int r = 0; r < ROWS; ++r) {
        for (int c = 0; c < COLS; ++c) {
            if (seats[r][c] == 0) return false;
        }
    }
    return true;
}

double calculatePrice(int row) {
    if (row <= 1) return FRONT_ROW_PRICE;
    if (row <= 3) return MID_ROW_PRICE;
    return BACK_ROW_PRICE;
}

// Clears invalid cin buffer states safely
void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Synchronize database records into 2D seating matrix at startup
void syncDatabaseToSeats() {
    for (const auto& b : bookings) {
        if (isSeatValid(b.seatRow, b.seatCol)) {
            seats[b.seatRow][b.seatCol] = 1;
        }
        if (b.bookingId >= nextBookingId) {
            nextBookingId = b.bookingId + 1;
        }
    }
}

// ==========================================
// 3. Member 1: Seating & Booking Core
// ==========================================

void displaySeats() {
    cout << "\n============================================\n";
    cout << "             SEATING ARRANGEMENT            \n";
    cout << "============================================\n";
    cout << "       ";
    for (int c = 0; c < COLS; ++c) {
        cout << "Col " << c << "  ";
    }
    cout << "\n--------------------------------------------\n";

    for (int r = 0; r < ROWS; ++r) {
        cout << "Row " << r << " | ";
        for (int c = 0; c < COLS; ++c) {
            if (seats[r][c] == 0) {
                cout << "[ O ]  "; // Available
            } else {
                cout << "[ X ]  "; // Booked
            }
        }
        cout << "\n";
    }
    cout << "--------------------------------------------\n";
    cout << "Legend: [ O ] = Available | [ X ] = Booked\n";
    cout << "Screen: ------------------------------------\n";
    cout << "Price Tiers: Rows 0-1: $" << FRONT_ROW_PRICE 
         << " | Rows 2-3: $" << MID_ROW_PRICE 
         << " | Row 4: $" << BACK_ROW_PRICE << "\n\n";
}

void bookTicket() {
    cout << "\n--- Book a Ticket ---\n";

    // If theater is completely full, offer waitlist queue
    if (isTheaterFull()) {
        cout << "Notice: Theater is completely full!\n";
        cout << "Would you like to join the Waiting List? (y/n): ";
        char choice;
        cin >> choice;
        clearInputBuffer();
        if (choice == 'y' || choice == 'Y') {
            cout << "Enter customer name: ";
            string name;
            getline(cin, name);
            if (name.empty()) {
                cout << "Error: Name cannot be empty.\n";
                return;
            }
            waitlist.push(name);
            cout << "Successfully added " << name << " to the waiting list! (Position: " << waitlist.size() << ")\n";
        }
        return;
    }

    displaySeats();

    string name;
    cout << "Enter customer name: ";
    clearInputBuffer();
    getline(cin, name);
    if (name.empty()) {
        cout << "Error: Customer name cannot be empty.\n";
        return;
    }

    int r = -1, c = -1;
    cout << "Enter Row (0-" << ROWS - 1 << "): ";
    if (!(cin >> r)) {
        cout << "Error: Invalid row input.\n";
        clearInputBuffer();
        return;
    }

    cout << "Enter Column (0-" << COLS - 1 << "): ";
    if (!(cin >> c)) {
        cout << "Error: Invalid column input.\n";
        clearInputBuffer();
        return;
    }

    if (!isSeatValid(r, c)) {
        cout << "Error: Seat (" << r << ", " << c << ") is out of valid bounds.\n";
        return;
    }

    if (!isSeatAvailable(r, c)) {
        cout << "Error: Seat (" << r << ", " << c << ") is already booked!\n";
        return;
    }

    // Allocate seat
    seats[r][c] = 1;
    double price = calculatePrice(r);

    Booking newBooking;
    newBooking.bookingId = nextBookingId++;
    newBooking.customerName = name;
    newBooking.movieName = FIXED_MOVIE;
    newBooking.seatRow = r;
    newBooking.seatCol = c;
    newBooking.ticketPrice = price;

    // Store in vector, push to undo stack, and persist in MySQL
    bookings.push_back(newBooking);
    undoStack.push(newBooking);
    saveBooking(newBooking);

    cout << "\nTicket Confirmed!\n";
    cout << "Booking ID  : " << newBooking.bookingId << "\n";
    cout << "Customer    : " << newBooking.customerName << "\n";
    cout << "Movie       : " << newBooking.movieName << "\n";
    cout << "Seat        : Row " << newBooking.seatRow << ", Col " << newBooking.seatCol << "\n";
    cout << "Price       : $" << fixed << setprecision(2) << newBooking.ticketPrice << "\n";
}

void cancelTicket() {
    cout << "\n--- Cancel Ticket ---\n";
    if (bookings.empty()) {
        cout << "No active bookings found to cancel.\n";
        return;
    }

    int id;
    cout << "Enter Booking ID to cancel: ";
    if (!(cin >> id)) {
        cout << "Error: Invalid Booking ID format.\n";
        clearInputBuffer();
        return;
    }

    int foundIndex = -1;
    for (size_t i = 0; i < bookings.size(); ++i) {
        if (bookings[i].bookingId == id) {
            foundIndex = static_cast<int>(i);
            break;
        }
    }

    if (foundIndex == -1) {
        cout << "Error: Booking ID " << id << " not found.\n";
        return;
    }

    Booking cancelled = bookings[foundIndex];
    int freedRow = cancelled.seatRow;
    int freedCol = cancelled.seatCol;

    // Free the seat, erase from vector, and delete from MySQL
    seats[freedRow][freedCol] = 0;
    bookings.erase(bookings.begin() + foundIndex);
    deleteBooking(id);

    cout << "Booking ID " << id << " for " << cancelled.customerName << " has been cancelled.\n";
    cout << "Seat Row " << freedRow << ", Col " << freedCol << " is now released.\n";

    // FIFO Waitlist Demonstration: If someone is waiting, automatically assign released seat!
    if (!waitlist.empty()) {
        string nextPerson = waitlist.front();
        waitlist.pop();

        seats[freedRow][freedCol] = 1;
        double price = calculatePrice(freedRow);

        Booking autoBooking;
        autoBooking.bookingId = nextBookingId++;
        autoBooking.customerName = nextPerson;
        autoBooking.movieName = FIXED_MOVIE;
        autoBooking.seatRow = freedRow;
        autoBooking.seatCol = freedCol;
        autoBooking.ticketPrice = price;

        bookings.push_back(autoBooking);
        undoStack.push(autoBooking);
        saveBooking(autoBooking);

        cout << "\n[FIFO Notification] Released seat allocated to first waitlist customer:\n";
        cout << "-> " << nextPerson << " assigned Seat (" << freedRow << ", " << freedCol 
             << ") with Booking ID #" << autoBooking.bookingId << "\n";
    }
}

// ==========================================
// 4. Member 2: STL, Searching, Sorting & DSA
// ==========================================

void displayBookings() {
    cout << "\n========================================================================\n";
    cout << "                            ACTIVE BOOKINGS                             \n";
    cout << "========================================================================\n";
    if (bookings.empty()) {
        cout << "No active bookings to show.\n";
        return;
    }

    cout << left << setw(12) << "Booking ID"
         << setw(20) << "Customer Name"
         << setw(16) << "Movie"
         << setw(12) << "Seat (R, C)"
         << setw(10) << "Price ($)" << "\n";
    cout << "------------------------------------------------------------------------\n";

    for (const auto& b : bookings) {
        string seatStr = "(" + to_string(b.seatRow) + ", " + to_string(b.seatCol) + ")";
        cout << left << setw(12) << b.bookingId
             << setw(20) << b.customerName
             << setw(16) << b.movieName
             << setw(12) << seatStr
             << setw(10) << fixed << setprecision(2) << b.ticketPrice << "\n";
    }
    cout << "------------------------------------------------------------------------\n";
    cout << "Total Active Bookings: " << bookings.size() << "\n";
}

void searchBooking() {
    cout << "\n--- Search Booking by Customer Name (Linear Search) ---\n";
    if (bookings.empty()) {
        cout << "No bookings exist to search.\n";
        return;
    }

    cout << "Enter customer name to search: ";
    clearInputBuffer();
    string query;
    getline(cin, query);

    bool found = false;
    cout << "\nSearch Results for \"" << query << "\":\n";
    cout << "------------------------------------------------------------------------\n";

    // Syllabus: Linear Search O(N)
    for (const auto& b : bookings) {
        if (b.customerName == query) {
            found = true;
            cout << "Found Booking ID : " << b.bookingId << "\n";
            cout << "Customer Name    : " << b.customerName << "\n";
            cout << "Movie            : " << b.movieName << "\n";
            cout << "Seat Allocated   : Row " << b.seatRow << ", Col " << b.seatCol << "\n";
            cout << "Price Paid       : $" << fixed << setprecision(2) << b.ticketPrice << "\n";
            cout << "------------------------------------------------------------------------\n";
        }
    }

    if (!found) {
        cout << "No bookings found matching \"" << query << "\".\n";
    }
}

void sortBookings() {
    cout << "\n--- Sort Bookings Alphabetically (std::sort) ---\n";
    if (bookings.empty()) {
        cout << "No bookings available to sort.\n";
        return;
    }

    // Syllabus: std::sort O(N log N) with lambda predicate comparing customer names
    sort(bookings.begin(), bookings.end(), [](const Booking& a, const Booking& b) {
        return a.customerName < b.customerName;
    });

    cout << "Bookings successfully sorted alphabetically by customer name!\n";
    displayBookings();
}

void showWaitlist() {
    cout << "\n============================================\n";
    cout << "           WAITING LIST (FIFO QUEUE)        \n";
    cout << "============================================\n";
    if (waitlist.empty()) {
        cout << "Waitlist is currently empty.\n";
        return;
    }

    // Traverse queue without destroying original state
    queue<string> tempQueue = waitlist;
    int position = 1;

    while (!tempQueue.empty()) {
        cout << position << ". " << tempQueue.front() << "\n";
        tempQueue.pop();
        position++;
    }
    cout << "--------------------------------------------\n";
    cout << "Total waiting customers: " << waitlist.size() << "\n";
}

void undoLastBooking() {
    cout << "\n--- Undo Last Booking (LIFO Stack) ---\n";
    if (undoStack.empty()) {
        cout << "Undo Stack is empty. No bookings to revert.\n";
        return;
    }

    Booking last = undoStack.top();
    undoStack.pop();

    // Check if the booking is still active in the bookings list
    auto it = find_if(bookings.begin(), bookings.end(), [&](const Booking& b) {
        return b.bookingId == last.bookingId;
    });

    if (it != bookings.end()) {
        // Free the seat, remove from vector, and delete from MySQL
        seats[last.seatRow][last.seatCol] = 0;
        bookings.erase(it);
        deleteBooking(last.bookingId);

        cout << "Reverted Booking ID #" << last.bookingId << " for " << last.customerName << "!\n";
        cout << "Seat (" << last.seatRow << ", " << last.seatCol << ") is now marked available again.\n";
    } else {
        cout << "Notice: Booking ID #" << last.bookingId << " was already cancelled or altered.\n";
    }
}

// ==========================================
// 5. Member 3: Menu Controller & Viva Guide
// ==========================================

void printMenu() {
    cout << "\n============================================\n";
    cout << "      CineSeat: Smart Ticket Booking        \n";
    cout << "============================================\n";
    cout << "1. Display Seats\n";
    cout << "2. Book Ticket\n";
    cout << "3. Cancel Ticket\n";
    cout << "4. View All Bookings\n";
    cout << "5. Search Booking (Linear Search)\n";
    cout << "6. Sort Bookings (std::sort)\n";
    cout << "7. Show Waiting List (Queue)\n";
    cout << "8. Undo Last Booking (Stack)\n";
    cout << "9. Exit\n";
    cout << "============================================\n";
    cout << "Enter your choice (1-9): ";
}

int main() {
    int choice = 0;

    cout << "\nWelcome to CineSeat — Smart Movie Ticket Booking System!\n";
    cout << "Now Screening: " << FIXED_MOVIE << " (Auditorium 1)\n";

    // Startup: Connect to MySQL, load persisted bookings, and synchronize 2D seat grid
    if (connectDatabase()) {
        loadBookings(bookings);
        syncDatabaseToSeats();
    }

    while (true) {
        printMenu();
        if (!(cin >> choice)) {
            cout << "Invalid input. Please enter a number between 1 and 9.\n";
            clearInputBuffer();
            continue;
        }

        switch (choice) {
            case 1:
                displaySeats();
                break;
            case 2:
                bookTicket();
                break;
            case 3:
                cancelTicket();
                break;
            case 4:
                displayBookings();
                break;
            case 5:
                searchBooking();
                break;
            case 6:
                sortBookings();
                break;
            case 7:
                showWaitlist();
                break;
            case 8:
                undoLastBooking();
                break;
            case 9:
                cout << "\nThank you for using CineSeat! Have a great movie experience.\n";
                closeDatabase();
                return 0;
            default:
                cout << "Invalid option (" << choice << "). Please select between 1 and 9.\n";
                break;
        }
    }

    closeDatabase();
    return 0;
}
