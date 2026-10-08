# CineSeat — Smart Movie Ticket Booking & Waitlist System

[![C++17](https://img.shields.io/badge/C%2B%2B-17-blue.svg)](https://isocpp.org/)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Build](https://img.shields.io/badge/build-passing-brightgreen.svg)]()
[![Platform](https://img.shields.io/badge/platform-Windows%20%7C%20Linux%20%7C%20macOS-lightgrey.svg)]()

> **Academic College C++ DSA Mini-Project**  
> Designed for high academic clarity, syllabus coverage, and a smooth 10-minute viva/demo presentation by a 3-member student team.

---

## 📌 Table of Contents
- [Project Overview](#-project-overview)
- [Official Project Scope](#-official-project-scope)
- [DSA Syllabus Coverage](#-dsa-syllabus-coverage)
- [Team Division (3 Students)](#-team-division-3-students)
- [Database Integration (MySQL)](#-database-integration-mysql)
- [Getting Started & Compilation](#-getting-started--compilation)
- [Viva & Demo Q&A Guide](#-viva--demo-qa-guide)
- [Project Rules & Constraints](#-project-rules--constraints)

---

## 🎬 Project Overview
**CineSeat** is a clean, menu-driven C++17 console application for booking movie tickets, viewing seating grids in real time, handling waiting lists when the auditorium reaches capacity, and supporting booking undos.

### Key Highlights:
- **No external bloat**: Zero dependencies beyond the C++ standard library.
- **Easy to trace**: Simple procedural functions operating over clear data structures.
- **Explainable**: Direct correlation between standard syllabus topics and project functions.

---

## 🎯 Official Project Scope

1. **Display Seats**: Visualizes the `5 x 6` seating arrangement (`0 = Available [ O ]`, `1 = Booked [ X ]`).
2. **Book Ticket**: Validates coordinates, verifies availability, calculates tier price, stores record in `vector`, and pushes to `stack`.
3. **Cancel Ticket**: Searches by unique Booking ID, frees the seat, and automatically reassigns it to the next customer in the waitlist queue if present (demonstrates FIFO).
4. **View All Bookings**: Formatted tabular view of all active movie bookings.
5. **Search Booking**: Performs **Linear Search** \(O(N)\) by customer name.
6. **Sort Bookings**: Sorts active bookings alphabetically by customer name using **`std::sort`** \(O(N \log N)\).
7. **Show Waiting List**: Traverses the waitlist queue without destroying container contents.
8. **Undo Last Booking**: Uses **LIFO Stack** to roll back the most recent ticket booking.
9. **Exit**: Gracefully exits the application.

---

## 📚 DSA Syllabus Coverage

| Data Structure / Algorithm | Representation in Code | Syllabus Topic | Academic Purpose | Time Complexity |
|---|---|---|---|---|
| **2D Array** | `int seats[5][6]` | Multidimensional Arrays | Real-time theater seating layout | \(O(1)\) access |
| **Structure** | `struct Booking` | User-defined Data Types | Encapsulates ticket entity | \(O(1)\) |
| **Dynamic Array** | `std::vector<Booking>` | STL Linear Containers | Resizable store of confirmed bookings | \(O(1)\) amortized push |
| **Queue** | `std::queue<string>` | FIFO Data Structure | Waitlist when hall is at capacity | \(O(1)\) push/pop |
| **Stack** | `std::stack<Booking>` | LIFO Data Structure | Undo history of recent bookings | \(O(1)\) push/pop |
| **Linear Search** | `searchBooking()` | Searching Algorithms | Locates customer bookings by name | \(O(N)\) |
| **Sorting** | `std::sort()` | Sorting Algorithms | Alphabetical sorting of bookings | \(O(N \log N)\) |

---

## 👥 Team Division (3 Students)

### Member 1: Seating & Booking Core
- **Responsibilities**:
  - 2D Seating Matrix (`seats[5][6]`)
  - `struct Booking` definition
  - Coordinate bound checking (`isSeatValid`) and availability checking (`isSeatAvailable`)
  - Row-based dynamic pricing tier calculation (`calculatePrice`)
  - Direct seat booking and cancellation memory updates

### Member 2: DSA & STL Algorithms
- **Responsibilities**:
  - Dynamic container handling (`std::vector<Booking>`)
  - Waiting queue FIFO implementation (`std::queue<string>`)
  - Undo stack LIFO implementation (`std::stack<Booking>`)
  - Linear Search algorithm implementation
  - `std::sort` with custom comparator/lambda
  - Big-O time and space complexity analysis

### Member 3: Persistence, UX & Integration
- **Responsibilities**:
  - MySQL Database schema (`schema.sql`) and query design
  - Menu controller loop and user experience
  - Input stream safety and edge-case sanitization (`clearInputBuffer`)
  - Build automation (`Makefile`, `CMakeLists.txt`)
  - Viva preparation and repository management

---

## 🗄️ Database Integration (MySQL)

A clean single-table schema is provided in [`sql/schema.sql`](file:///g:/Projects/CineSeat/sql/schema.sql):

```sql
CREATE DATABASE IF NOT EXISTS cinema_db;
USE cinema_db;

CREATE TABLE bookings (
    booking_id INT PRIMARY KEY,
    customer_name VARCHAR(100) NOT NULL,
    movie_name VARCHAR(100) NOT NULL,
    seat_row INT NOT NULL,
    seat_col INT NOT NULL,
    ticket_price DOUBLE NOT NULL
);
```

### Database Operations (`database.h` / `database.cpp`)
The database code is minimal and structured into 4 easy-to-explain functions:
1. `connectDatabase()`: Establishes a connection to MySQL using credentials from `db_config.env` (falls back gracefully to offline mode if MySQL is not running).
2. `loadBookings()`: Executes `SELECT * FROM bookings;` at application startup, populating `vector<Booking>` and marking occupied seats on `seats[5][6]`.
3. `saveBooking()`: Executes `INSERT INTO bookings ...` when a ticket is confirmed.
4. `deleteBooking()`: Executes `DELETE FROM bookings WHERE booking_id = ...` when a booking is cancelled or undone.

---

## 💻 Getting Started & Compilation

### Prerequisites
- Any C++17 compliant compiler (`g++`, `clang++`, or MSVC)
- MySQL Server (optional, runs in local fallback mode if offline)

### Configuration
Copy `db_config.example.env` to `db_config.env` and enter your MySQL server credentials:
```ini
DB_HOST=localhost
DB_USER=root
DB_PASS=your_password
DB_NAME=cinema_db
DB_PORT=3306
```

### Compilation using g++
```bash
# Compile with MySQL client library
g++ -std=c++17 -Wall -Wextra -O2 -I./include -L./lib -o cineseat.exe src/main.cpp src/database.cpp -llibmysql

# Run
./cineseat.exe
```

### Using Makefile
```bash
make
make run
```

---

## 🎓 Viva & Demo Q&A Guide

**Q1: Why use a 2D array for seating?**  
*Answer*: The theater layout naturally forms rows and columns. A 2D array provides \(O(1)\) constant time access to check or update seat availability using row and column indices.

**Q2: Why use a Queue for the waiting list?**  
*Answer*: A Queue follows the First-In-First-Out (FIFO) principle, ensuring fairness. The person who joined the waitlist first is served first when a seat is cancelled.

**Q3: How does the Undo feature work?**  
*Answer*: An STL `stack<Booking>` records bookings in Last-In-First-Out (LIFO) order. When undo is requested, `undoStack.top()` reveals the most recent booking, which is then popped and rolled back in both the seating matrix and bookings vector.

**Q4: What is the time complexity of searching and sorting?**  
*Answer*: Searching uses Linear Search with \(O(N)\) time complexity. Sorting uses `std::sort` which implements Introsort (a hybrid of Quicksort, Heapsort, and Insertion Sort) with \(O(N \log N)\) time complexity.

---

## 📄 License
This project is open-source under the [MIT License](LICENSE).
