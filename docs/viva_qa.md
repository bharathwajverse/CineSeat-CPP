# CineSeat — Frequently Asked Viva Questions & Model Answers

### General Architecture
**Q1: What are the main data structures used in this project?**
- **2D Array (`int seats[5][6]`)**: Represents the theater auditorium grid.
- **Structure (`struct Booking`)**: Encapsulates ticket attributes (ID, customer, movie, row, col, price).
- **STL `std::vector<Booking>`**: Dynamically stores confirmed bookings in memory.
- **STL `std::queue<string>`**: Implements the waitlist queue adhering to FIFO order.
- **STL `std::stack<Booking>`**: Implements undo functionality adhering to LIFO order.

---

### Seating & Pricing
**Q2: Why use a 2D array instead of a 1D array for seating?**
- A 2D array mirrors the physical layout of rows and columns.
- Direct index access `seats[row][col]` provides $O(1)$ constant-time lookup and updates without coordinate mathematical transformations like `index = row * COLS + col`.

**Q3: How is dynamic pricing calculated?**
- Front rows (Rows 0-1): $150.00
- Middle rows (Rows 2-3): $200.00
- Back VIP / Recliner row (Row 4): $250.00
- Computed in $O(1)$ time by inspecting the row index.

---

### Stacks & Queues
**Q4: What is the FIFO principle and where is it used?**
- **FIFO** stands for First-In, First-Out.
- Used in the **Waiting List** (`std::queue<string>`). When the theater is at 100% capacity (30 seats booked), new customers are placed in the queue. When an active booking is cancelled, the head of the queue (`waitlist.front()`) is popped and automatically assigned the freed seat.

**Q5: What is the LIFO principle and where is it used?**
- **LIFO** stands for Last-In, First-Out.
- Used in the **Undo feature** (`std::stack<Booking>`). Every time a ticket is booked, the booking object is pushed onto the stack. Selecting Undo pops the top element and restores the seat and database state.

---

### Searching & Sorting
**Q6: What is the time complexity of the search operation?**
- We use **Linear Search** to find bookings by customer name.
- Best Case: $O(1)$ (match is the first element).
- Worst Case: $O(N)$ (element is at the end or not present).
- Space Complexity: $O(1)$ auxiliary memory.

**Q7: How does `std::sort` work in this project?**
- It sorts bookings alphabetically by `customerName` using a custom lambda comparator:
  `[](const Booking& a, const Booking& b) { return a.customerName < b.customerName; }`
- Internal algorithm: **Introsort** (hybrid of Quicksort, Heapsort, and Insertion Sort).
- Average and Worst-Case Time Complexity: $O(N \log N)$.

---

### Database & Persistence
**Q8: How does the application maintain consistency between MySQL and memory?**
- **Startup**: `connectDatabase()` connects, and `loadBookings()` performs `SELECT * FROM bookings;`. Seats are marked occupied on the 2D grid.
- **Booking**: In-memory vector push is immediately persisted using `INSERT INTO bookings ...`.
- **Cancellation / Undo**: In-memory erase is immediately mirrored using `DELETE FROM bookings WHERE booking_id = ...`.
