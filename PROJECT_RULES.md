# CineSeat — Smart Movie Ticket Booking & Waitlist System
## Project Rules & Constraints

### 1. Primary Objectives
- Keep the project **small, simple, readable, and easy to explain** for a 10-minute viva/demo for 3 students.
- **Optimize for academic clarity, syllabus coverage, and explainability**, NOT enterprise or production software.
- Strictly adhere to C++17 standards.

---

### 2. Official Project Scope (9 Menu Options)
1. **Display Seats** (`seats[5][6]` status: `0 = Available`, `1 = Booked`)
2. **Book Ticket** (Validate coordinates, calculate price, insert into `vector<Booking>`, push to `stack<Booking>`)
3. **Cancel Ticket** (Search by Booking ID, free seat, remove from `vector<Booking>`, assign to first queue waitlist if any)
4. **View All Bookings** (List all active bookings)
5. **Search Booking** (Linear search by customer name)
6. **Sort Bookings** (`std::sort` by customer name)
7. **Show Waiting List** (Display names in FIFO `queue<string>`)
8. **Undo Last Booking** (Pop from LIFO `stack<Booking>`, free seat, remove from list)
9. **Exit**

---

### 3. Data Structures & Syllabus Alignment
- **2D Array (`int seats[5][6]`)**: Matrix representation of cinema seating arrangement.
- **Structure (`struct Booking`)**: Record containing `bookingId`, `customerName`, `movieName`, `seatRow`, `seatCol`, `ticketPrice`.
- **STL `std::vector<Booking>`**: Dynamic linear container storing active tickets.
- **STL `std::queue<string>`**: First-In-First-Out (FIFO) queue for fair waitlist management.
- **STL `std::stack<Booking>`**: Last-In-First-Out (LIFO) stack for undoing the most recent booking.
- **Searching**: Linear Search \(O(N)\) over bookings by customer name.
- **Sorting**: `std::sort` \(O(N \log N)\) algorithm by customer name alphabetically.
- **Complexity Analysis**: Explicit time and space complexity documented for every operation.

---

### 4. Database Integration Design (Academic Schema)
- **Engine**: MySQL / MariaDB (optional backend persistence / schema script provided).
- **Single Table**:
  ```sql
  CREATE TABLE bookings (
      booking_id INT PRIMARY KEY,
      customer_name VARCHAR(100) NOT NULL,
      movie_name VARCHAR(100) NOT NULL,
      seat_row INT NOT NULL,
      seat_col INT NOT NULL,
      ticket_price DOUBLE NOT NULL
  );
  ```
- Fixed movie title (e.g., *"Interstellar"*). No dynamic movie fetching or complex schema relations.

---

### 5. Team Division (3 Members)
- **Member 1 (Seating & Booking Core)**:
  - 2D seating array matrix (`seats[5][6]`)
  - `struct Booking`
  - Coordinate validation & price calculation
  - Seat assignment & cancellation logic
- **Member 2 (DSA & STL Algorithms)**:
  - Vector, Queue (Waitlist FIFO), and Stack (Undo LIFO) operations
  - Linear search implementation
  - `std::sort` implementation
  - Algorithm complexity and viva presentation
- **Member 3 (Database, Integration & Build)**:
  - Database schema (`schema.sql`) & CRUD mapping
  - Input validation, menu loop, and terminal UX
  - Build scripts, Git versioning, and documentation

---

### 6. Strict "DO NOT ADD" List
- ❌ No login / registration / authentication
- ❌ No frontend frameworks (React, Vue, Node.js, HTML/CSS)
- ❌ No REST APIs / web servers
- ❌ No payment gateways / online payment / QR codes
- ❌ No multiple theaters / multiple cities / multiple screening rooms
- ❌ No external movie APIs (TMDB/OMDb)
- ❌ No cloud deployment / Docker / Kubernetes
- ❌ No complex OOP hierarchies / multiple inheritance / design pattern overkill
- ❌ No extra database tables or foreign key webs
