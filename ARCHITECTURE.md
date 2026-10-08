# CineSeat — Architecture & Technical Specifications

## 1. System Overview
CineSeat is an academic, console-based Smart Movie Ticket Booking and Waitlist Management system implemented in **C++17**. It models real-world cinema ticket allocation while focusing strictly on core Data Structures and Algorithms (DSA) syllabi: Arrays, Structs, Linked Containers, Queues, Stacks, Searching, and Sorting.

---

## 2. Component Architecture

```
+--------------------------------------------------------------+
|                     User Terminal (I/O)                      |
+--------------------------------------------------------------+
                                |
                                v
+--------------------------------------------------------------+
|               CineSeat Core Menu Controller                  |
|                 (9 Menu-Driven Actions)                      |
+--------------------------------------------------------------+
        |                  |                    |
        v                  v                    v
+---------------+  +------------------+  +--------------------+
| Member 1      |  | Member 2         |  | Member 3           |
| Seating &     |  | DSA & STL Ops    |  | Persistence & UX   |
| Bookings      |  |                  |  |                    |
|               |  |                  |  |                    |
| - 2D Array    |  | - vector<Booking>|  | - schema.sql       |
|   seats[5][6] |  | - queue<string>  |  | - Input Validation |
| - struct      |  | - stack<Booking> |  | - DB Sync Mock /   |
|   Booking     |  | - Linear Search  |  |   Connector Adapter|
| - Price Calc  |  | - std::sort      |  | - Viva Explanations|
+---------------+  +------------------+  +--------------------+
```

---

## 3. Data Structure Specifications

| Data Structure | C++ Representation | Academic Syllabus Concept | Primary Use Case |
|---|---|---|---|
| **2D Array** | `int seats[5][6]` | Matrix / Multi-dimensional Array | Visual theater grid; 0 = Empty, 1 = Booked |
| **Structure** | `struct Booking` | User-defined Types / Records | Encapsulates ticket entity fields |
| **Dynamic Array** | `std::vector<Booking>` | STL Linear Container | Stores active ticket records |
| **Queue** | `std::queue<string>` | FIFO (First-In, First-Out) | Waitlist when hall is at full capacity |
| **Stack** | `std::stack<Booking>` | LIFO (Last-In, First-Out) | Undo history for the most recent booking |
| **Searching** | Linear Search | \(O(N)\) Traversal | Find booking by customer name |
| **Sorting** | `std::sort` | \(O(N \log N)\) Introsort | Alphabetical listing of customer bookings |

---

## 4. Time and Space Complexity Summary

| Operation | Time Complexity | Space Complexity | Explanation |
|---|---|---|---|
| `displaySeats()` | \(O(R \times C) = O(30) = O(1)\) | \(O(1)\) | Traverses fixed 5x6 grid |
| `bookTicket()` | \(O(1)\) | \(O(1)\) | Direct coordinate index access + push |
| `cancelTicket()` | \(O(N)\) | \(O(1)\) | Linear search for `bookingId` + vector erase |
| `displayBookings()` | \(O(N)\) | \(O(1)\) | Linear traversal of \(N\) active bookings |
| `searchBooking()` | \(O(N)\) | \(O(1)\) auxiliary | Iterates over vector comparing names |
| `sortBookings()` | \(O(N \log N)\) | \(O(\log N)\) | `std::sort` dual-pivot introsort |
| `showWaitlist()` | \(O(W)\) | \(O(W)\) auxiliary | Traversal of \(W\) waitlisted customers |
| `undoLastBooking()` | \(O(N)\) | \(O(1)\) | Pops top element \(O(1)\), frees seat and vector entry |

---

## 5. File Structure
```
CineSeat/
├── CMakeLists.txt          # Standard CMake build script
├── Makefile                # Fast g++ compilation targets
├── PROJECT_RULES.md        # Academic guidelines & constraints
├── ARCHITECTURE.md         # Technical architecture & complexity
├── README.md               # Repository documentation & Viva guide
├── schema.sql              # MySQL database schema & sample queries
├── .gitignore              # Ignores build artifacts and binaries
└── src/
    └── main.cpp            # Clean, modular C++17 core application
```
