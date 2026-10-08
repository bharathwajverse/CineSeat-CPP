# CineSeat — Live Demonstration Script & Test Workflow

Follow this step-by-step test procedure to demonstrate all 9 menu items smoothly during your project presentation.

---

## 📋 Step-by-Step Test Procedure

### Test 1: Display Initial Empty Grid (Option 1)
- **Input**: `1`
- **Expected Result**: A 5x6 matrix of `[ O ]` (Available) is printed with clear Row/Column coordinates and pricing breakdown.

### Test 2: Book Multiple Tickets (Option 2)
- **Action**: Book Seat Row 0, Col 0 for "Alice" ($150.00).
- **Action**: Book Seat Row 2, Col 3 for "Charlie" ($200.00).
- **Action**: Book Seat Row 4, Col 5 for "Bob" ($250.00).
- **Expected Result**: System confirms each booking with auto-incremented Booking IDs (101, 102, 103) and saves each into MySQL.

### Test 3: View Active Bookings (Option 4)
- **Input**: `4`
- **Expected Result**: Clean tabular display showing all 3 bookings, customer names, allocated seats, and prices.

### Test 4: Search Booking (Option 5)
- **Input**: `5` -> Query: `Alice`
- **Expected Result**: Linear search locates Alice's record in $O(N)$ time and displays ticket details.
- **Input**: `5` -> Query: `Zack`
- **Expected Result**: Reports "No bookings found matching Zack".

### Test 5: Sort Bookings (Option 6)
- **Input**: `6`
- **Expected Result**: Runs `std::sort` ($O(N \log N)$) and re-displays active bookings in alphabetical order:
  1. Alice
  2. Bob
  3. Charlie

### Test 6: Undo Last Booking (Option 8)
- **Input**: `8`
- **Expected Result**: Demonstrates LIFO stack behavior. Reverts the most recent booking (Bob, Seat (4, 5)), marks Seat (4, 5) back to `[ O ]`, and removes the record from MySQL.

### Test 7: Cancel Ticket & Verify Seat Release (Option 3)
- **Input**: `3` -> Booking ID: `101` (Alice)
- **Expected Result**: Alice's booking is removed from memory and deleted from MySQL. Seat (0, 0) is released.

### Test 8: Exit & Verify Persistence Reload (Option 9)
- **Action**: Exit via `9`.
- **Action**: Restart application (`./cineseat.exe`).
- **Expected Result**: Startup message confirms connection to MySQL and reloads Charlie's booking (Seat (2, 3)), automatically restoring the occupied seat `[ X ]`.
