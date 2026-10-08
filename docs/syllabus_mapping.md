# CineSeat — Syllabus Mapping & Pedagogical Alignment

This document correlates every course syllabus requirement to the exact source lines and functions implemented in CineSeat.

---

## 📌 Syllabus Topic Matrix

| Syllabus Topic | Practical Topic in College Lab | Implementation in CineSeat | File & Function |
|---|---|---|---|
| **Multidimensional Arrays** | 2D Arrays, Matrix indexing, state representation | `int seats[5][6]` | `src/main.cpp` -> `displaySeats()`, `bookTicket()` |
| **Structures (Records)** | User-defined heterogenous records | `struct Booking` | `src/database.h` -> `struct Booking` |
| **Linear Containers (STL)** | Dynamic Arrays, Vector manipulation | `std::vector<Booking>` | `src/main.cpp` -> `bookings.push_back()`, `erase()` |
| **Queues (FIFO)** | Queue ADT, Enqueue, Dequeue, Peek | `std::queue<string>` | `src/main.cpp` -> `waitlist.push()`, `waitlist.pop()` |
| **Stacks (LIFO)** | Stack ADT, Push, Pop, Top | `std::stack<Booking>` | `src/main.cpp` -> `undoStack.push()`, `undoStack.pop()` |
| **Searching Algorithms** | Linear Search, element matching | Name lookups | `src/main.cpp` -> `searchBooking()` |
| **Sorting Algorithms** | Comparison sorts, Introsort, Lambdas | Alphabetical sorting | `src/main.cpp` -> `sortBookings()` via `std::sort()` |
| **Database Persistence** | SQL DDL & DML, CRUD operations | MySQL 8.0 C Connector | `src/database.cpp` -> `saveBooking()`, `deleteBooking()` |
| **Complexity Analysis** | Time and Space Big-O Analysis | Mathematical evaluation | `ARCHITECTURE.md` |

---

## 💡 Key Architectural Decisions for Students

1. **Why avoid OOP class hierarchies in this mini-project?**
   - In a 10-minute viva, examiners assess fundamental DSA concepts first. Procedural modular functions with clean structs allow each student to explain their exact function without cognitive overhead from inheritance or polymorphic virtual tables.

2. **Why keep SQL operations minimal?**
   - Keeping queries strictly to `SELECT`, `INSERT`, and `DELETE` on a single table ensures that every query can be recited and diagrammed on a whiteboard during the viva examination.
