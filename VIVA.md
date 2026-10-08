# CineSeat — 20 Likely Viva Questions & Simple Answers

### Category 1: Seating & Arrays
**Q1: Why use a 2D array for the seating arrangement?**  
**A:** Cinema halls are organized in rows and columns. A 2D array `seats[5][6]` gives instant $O(1)$ coordinate access and naturally represents the theater layout.

**Q2: What do the integer values in `seats[5][6]` represent?**  
**A:** `0` represents an available seat (`[ O ]`), and `1` represents an already booked seat (`[ X ]`).

**Q3: What is the time complexity of checking seat availability?**  
**A:** $O(1)$ constant time, because it is a direct array index check `seats[row][col] == 0`.

**Q4: How does dynamic pricing work?**  
**A:** `calculatePrice(row)` checks the row index: Rows 0-1 cost $150 (Front), Rows 2-3 cost $200 (Middle), and Row 4 costs $250 (VIP Recliner).

---

### Category 2: Structures & STL Containers
**Q5: Why did you use a `struct` instead of a `class` for `Booking`?**  
**A:** `struct Booking` represents a plain data record with heterogeneous fields (`int`, `string`, `double`). A struct keeps the code simple and readable without unnecessary OOP boilerplate.

**Q6: Why is `std::vector` preferred over a standard 1D static array for storing bookings?**  
**A:** A static array has a fixed capacity. An STL `std::vector` dynamically grows and shrinks as tickets are booked and cancelled, providing $O(1)$ amortized insertion.

**Q7: How do you remove a cancelled booking from the vector?**  
**A:** We find the element's iterator using its booking ID and call `bookings.erase(iterator)`, which shifts subsequent elements in $O(N)$ time.

---

### Category 3: Queues & Stacks (FIFO vs. LIFO)
**Q8: What is the FIFO principle and where is it demonstrated?**  
**A:** First-In, First-Out (FIFO) means the first element inserted is the first one removed. It is used in the waiting list (`std::queue<string>`) when all seats are full.

**Q9: What happens when a seat is cancelled while customers are waiting in the queue?**  
**A:** The application extracts the front customer using `waitlist.front()`, pops them with `waitlist.pop()`, and automatically assigns the released seat to them.

**Q10: What is the LIFO principle and where is it demonstrated?**  
**A:** Last-In, First-Out (LIFO) means the most recently added item is the first one removed. It is used in the Undo feature (`std::stack<Booking>`).

**Q11: How does `undoLastBooking()` work?**  
**A:** It inspects `undoStack.top()` to get the latest booking, pops it with `undoStack.pop()`, frees the corresponding seat matrix cell, removes the entry from the vector, and deletes it from MySQL.

**Q12: What happens if Undo is called on an empty stack?**  
**A:** It checks `undoStack.empty()` beforehand and safely informs the user without causing runtime crashes.

---

### Category 4: Searching & Sorting Algorithms
**Q13: Which search algorithm is implemented in Option 5?**  
**A:** Linear Search. It iterates through the `bookings` vector from index 0 to $N-1$ comparing each customer's name with the search query.

**Q14: What is the time and space complexity of Linear Search?**  
**A:** Time complexity is $O(N)$ worst-case; Auxiliary space complexity is $O(1)$.

**Q15: What sorting algorithm does `std::sort` use in Option 6?**  
**A:** It uses **Introsort**, which is a hybrid sorting algorithm combining Quicksort, Heapsort, and Insertion Sort.

**Q16: What is the time complexity of `std::sort`?**  
**A:** Both average and worst-case time complexity are $O(N \log N)$.

**Q17: How is the sorting order defined?**  
**A:** Using a C++ lambda comparator: `[](const Booking& a, const Booking& b) { return a.customerName < b.customerName; }`, which sorts alphabetically from A to Z.

---

### Category 5: Database & Architecture
**Q18: What is the structure of the MySQL database?**  
**A:** We use a single database `cinema_db` and one table `bookings` with columns: `booking_id` (PRIMARY KEY), `customer_name`, `movie_name`, `seat_row`, `seat_col`, and `ticket_price`.

**Q19: How are data synchronized when the program starts?**  
**A:** `loadBookings()` runs `SELECT * FROM bookings;` and loads records into `vector<Booking>`. Then `syncDatabaseToSeats()` sets `seats[row][col] = 1` for all loaded bookings.

**Q20: What are the main advantages of this modular design?**  
**A:** 
1. **Academic Clarity**: Core DSA logic runs independently in memory.
2. **Separation of Concerns**: Database operations are isolated in `database.h` and `database.cpp`.
3. **Resilience**: The application runs smoothly even if MySQL is offline.
