# CineSeat — 10-Minute Viva Presentation Guide

This guide is specifically curated for a 3-student team presenting CineSeat in a college viva or laboratory examination.

---

## ⏱️ Recommended 10-Minute Presentation Breakdown

| Time Window | Speaker | Focus Area |
|---|---|---|
| **00:00 - 02:00** | Team Lead / Member 1 | Problem statement, project scope, and cinema matrix simulation |
| **02:00 - 05:00** | Member 1 & Member 2 | Core DSA concepts: 2D array, Struct, Queue FIFO, Stack LIFO |
| **05:00 - 07:30** | Member 2 | Algorithms: Linear Search vs. `std::sort` Introsort, Time/Space complexities |
| **07:30 - 09:00** | Member 3 | Persistence: MySQL schema, startup synchronization, CRUD operations |
| **09:00 - 10:00** | All Members | Live terminal execution, handling edge cases, answering examiner questions |

---

## 🎯 Individual Speaking Scripts

### Member 1: Seating & Booking Core
- **Key Concepts**: 2D Arrays, User-defined Records, Matrix coordinates.
- **Viva Pitch**:
  > *"Good morning professors. I implemented the physical theater layout using a 2D array `seats[5][6]`, where 0 represents available seats and 1 represents booked seats. When a ticket is reserved, row-based dynamic pricing is applied, coordinate bounds are verified in $O(1)$ time, and the reservation is encapsulated inside a `struct Booking`."*

### Member 2: Data Structures & Algorithms
- **Key Concepts**: STL Vector, Queue (FIFO), Stack (LIFO), Linear Search, `std::sort`.
- **Viva Pitch**:
  > *"I handled dynamic storage and algorithmic operations. Active bookings are maintained in an STL `vector<Booking>`. When the theater is at maximum capacity, customers enter an STL `queue<string>` demonstrating First-In-First-Out fairness. If a booking is cancelled, the first waiting customer receives the seat automatically. Additionally, an STL `stack<Booking>` allows Last-In-First-Out undo operations. Searching is accomplished via Linear Search in $O(N)$ time, and sorting is powered by `std::sort` in $O(N \log N)$ time."*

### Member 3: Database & Integration
- **Key Concepts**: MySQL integration, SQL Queries, Startup hydration, Stream validation.
- **Viva Pitch**:
  > *"I designed the persistence layer and user interface. We use a single-table schema `bookings` in MySQL (`cinema_db`). At startup, `loadBookings()` performs a `SELECT` query, populating the vector and synchronizing the 2D matrix. Confirmed tickets execute `INSERT`, while cancellations and undos execute `DELETE`. The database layer is decoupled and includes safe environment configurations and offline fallback."*
