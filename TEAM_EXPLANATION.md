# CineSeat — Team Division & Explanation Guide

This guide assigns project components to exactly 3 students and equips each student with the concepts, functions, Q&A, and a 2-minute viva presentation script.

---

# MEMBER 1 — Seating and Booking

### 1. Files & Functions to Understand
- **Files**: [`src/main.cpp`](file:///g:/Projects/CineSeat/src/main.cpp), [`src/database.h`](file:///g:/Projects/CineSeat/src/database.h)
- **Functions**:
  - `isSeatValid(int row, int col)`
  - `isSeatAvailable(int row, int col)`
  - `isTheaterFull()`
  - `calculatePrice(int row)`
  - `displaySeats()`
  - `bookTicket()`
  - `cancelTicket()` (seat release logic)

### 2. Core DSA Concepts
- **2D Arrays (`int seats[5][6]`)**: Matrix indexing where `0 = Available` and `1 = Booked`.
- **User-Defined Structure (`struct Booking`)**: Encapsulates ticket entity properties.
- **Constant Time Access $O(1)$**: Instant boundary and availability lookups via row and column coordinates.
- **Dynamic Pricing Strategy**: Tier-based pricing calculated based on seat row position.

### 3. Expected Viva Questions & Simple Answers
- **Q: Why use a 2D array instead of a 1D array?**  
  *A:* Cinema halls have physical rows and columns. A 2D array allows direct coordinate access (`seats[r][c]`) in $O(1)$ time without needing coordinate conversion math (`r * COLS + c`).
- **Q: How do you prevent booking an already booked seat?**  
  *A:* `isSeatAvailable()` checks if `seats[row][col] == 0`. If it equals 1, the program rejects the booking with an error message.
- **Q: How is ticket price calculated?**  
  *A:* `calculatePrice()` assigns $150 to Rows 0-1 (Front), $200 to Rows 2-3 (Middle), and $250 to Row 4 (VIP/Recliner).

### 4. 2-Minute Explanation Script
> *"Good morning professors. I am responsible for the Seating Arrangement and Booking Core in CineSeat.*  
> *I modeled the cinema hall using a 5x6 2D array matrix: `int seats[5][6]`, where 0 represents an available seat and 1 represents a booked seat.*  
> *When a customer books a ticket using Option 2, `isSeatValid()` ensures the coordinates are within bounds, and `isSeatAvailable()` prevents double bookings in $O(1)$ time.*  
> *We implemented dynamic row pricing: front rows cost $150, middle rows cost $200, and back VIP recliners cost $250. Once confirmed, all ticket details are grouped into a `struct Booking` instance, the seat matrix cell is flipped to 1, and the seat is visually displayed on our terminal screen.*  
> *During cancellation, the seat cell is reset back to 0 so it can immediately be booked by another customer."*

---

# MEMBER 2 — Stack, Queue, STL, Search and Sort

### 1. Files & Functions to Understand
- **Files**: [`src/main.cpp`](file:///g:/Projects/CineSeat/src/main.cpp)
- **Functions**:
  - `displayBookings()`
  - `searchBooking()`
  - `sortBookings()`
  - `showWaitlist()`
  - `undoLastBooking()`
  - Cancellation queue auto-assignment inside `cancelTicket()`

### 2. Core DSA Concepts
- **STL Dynamic Array (`std::vector<Booking>`)**: Dynamic contiguous container storing active bookings with $O(1)$ amortized insertion.
- **FIFO Queue (`std::queue<string>`)**: First-In, First-Out waiting list when the cinema is at full capacity (30 seats).
- **LIFO Stack (`std::stack<Booking>`)**: Last-In, First-Out undo mechanism to roll back recent reservations.
- **Linear Search**: $O(N)$ sequential search through bookings comparing customer names.
- **Sorting (`std::sort`)**: $O(N \log N)$ Introsort algorithm using a custom lambda comparator.

### 3. Expected Viva Questions & Simple Answers
- **Q: Where and why is a Queue used?**  
  *A:* In the waiting list (`waitlist`). It enforces the First-In, First-Out (FIFO) rule: the customer who joined the waitlist first gets the first released seat when someone cancels.
- **Q: How does the Undo feature work using a Stack?**  
  *A:* Every booking is pushed to `undoStack`. When Option 8 is selected, `undoStack.top()` accesses the most recent booking, pops it (LIFO), frees the corresponding seat matrix cell, and removes the booking from the vector.
- **Q: What algorithm does `std::sort` use and what is its complexity?**  
  *A:* It uses Introsort (a hybrid of Quicksort, Heapsort, and Insertion Sort) with an optimal time complexity of $O(N \log N)$.

### 4. 2-Minute Explanation Script
> *"Good morning professors. I am responsible for the Data Structures, STL containers, Searching, and Sorting in CineSeat.*  
> *We use an STL `vector<Booking>` to store all active customer bookings dynamically in memory.*  
> *To demonstrate real-world Queue behavior, when all 30 seats are full, customers are placed into an STL `queue<string>`. This implements FIFO (First-In, First-Out) fairness: whenever an active booking is cancelled, the head of the queue is dequeued using `waitlist.pop()` and automatically allocated the released seat.*  
> *To demonstrate Stack behavior, every confirmed booking is pushed to an STL `stack<Booking>`. The Undo feature pops the top element (LIFO order), releasing that seat and rolling back the action.*  
> *For searching, `searchBooking()` runs a Linear Search in $O(N)$ time to match customer names.*  
> *For sorting, `sortBookings()` runs `std::sort()` in $O(N \log N)$ time with a custom lambda comparator to organize bookings alphabetically."*

---

# MEMBER 3 — MySQL and Database Integration

### 1. Files & Functions to Understand
- **Files**: [`src/database.h`](file:///g:/Projects/CineSeat/src/database.h), [`src/database.cpp`](file:///g:/Projects/CineSeat/src/database.cpp), [`sql/schema.sql`](file:///g:/Projects/CineSeat/sql/schema.sql), [`db_config.example.env`](file:///g:/Projects/CineSeat/db_config.example.env)
- **Functions**:
  - `connectDatabase()`
  - `closeDatabase()`
  - `loadBookings(vector<Booking>& list)`
  - `saveBooking(const Booking& b)`
  - `deleteBooking(int bookingId)`
  - `syncDatabaseToSeats()` in `main.cpp`

### 2. Core DSA & DBMS Concepts
- **Database Schema**: Single normalized relational table `bookings` in `cinema_db` matching `struct Booking`.
- **CRUD Operations**: Structured `SELECT`, `INSERT`, and `DELETE` queries.
- **Startup Hydration & State Sync**: Reading persisted records at program boot and populating both `vector<Booking>` and `seats[5][6]`.
- **Decoupled Architecture & Safe Config**: Credentials isolated in `db_config.env` with graceful fallback to offline in-memory execution if MySQL is unavailable.

### 3. Expected Viva Questions & Simple Answers
- **Q: What is the database schema for CineSeat?**  
  *A:* A single table `bookings` in `cinema_db` with columns: `booking_id` (PRIMARY KEY), `customer_name`, `movie_name`, `seat_row`, `seat_col`, and `ticket_price`.
- **Q: How does the application sync MySQL with the C++ 2D array?**  
  *A:* On startup, `connectDatabase()` establishes the connection and `loadBookings()` selects all active rows into the `vector`. Then `syncDatabaseToSeats()` iterates through the vector and marks `seats[b.seatRow][b.seatCol] = 1`.
- **Q: What happens if the MySQL server is offline?**  
  *A:* The application prints a notice and continues running seamlessly in offline in-memory mode, ensuring full reliability during demos.

### 4. 2-Minute Explanation Script
> *"Good morning professors. I designed the MySQL Database Integration and Persistence Layer for CineSeat.*  
> *We designed a relational database named `cinema_db` with a single table `bookings` whose schema directly mirrors our C++ `struct Booking`.*  
> *Our C++ backend connects to MySQL using the official C connector API. At application boot, `connectDatabase()` connects via `mysql_real_connect()` using credentials safely parsed from a configuration file.*  
> *`loadBookings()` performs a `SELECT` query, retrieving all persisted bookings into our `vector<Booking>` and marking occupied seats on the 2D matrix.*  
> *When a student books a ticket, `saveBooking()` executes an `INSERT` statement. When a ticket is cancelled or undone, `deleteBooking()` executes a `DELETE` statement by Booking ID.*  
> *All database operations are encapsulated in `database.h` and `database.cpp`, keeping the core DSA logic completely clean and modular."*
