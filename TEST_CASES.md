# CineSeat — Complete Test Cases & Demo Sequence

This document defines the exact live demo execution sequence, terminal inputs, and expected outcomes to demonstrate every feature and edge case to the examiner.

---

## 🧪 Quick Test Matrix

| # | Test Scenario | Menu Option & Input | Expected Output / Behavior |
|---|---|---|---|
| **1** | Invalid Menu Choice | `99` | Displays `Invalid option (99). Please select between 1 and 9.` |
| **2** | Display Initial Empty Grid | `1` | Prints 5x6 grid where all seats are `[ O ]` (Available). |
| **3** | View Empty Bookings | `4` | Displays `No active bookings to show.` |
| **4** | Search on Empty List | `5` -> `Alice` | Displays `No bookings exist to search.` |
| **5** | Undo on Empty Stack | `8` | Displays `Undo Stack is empty. No bookings to revert.` |
| **6** | Cancel on Empty List | `3` | Displays `No active bookings found to cancel.` |
| **7** | View Empty Waitlist | `7` | Displays `Waitlist is currently empty.` |
| **8** | Book Valid Seat | `2` -> `Alice`, `0`, `0` | Seat (0, 0) confirmed ($150). Auto-assigned Booking ID 101. Saved to MySQL. |
| **9** | Reject Out-of-Bounds Seat | `2` -> `Bob`, `9`, `9` | Error: `Seat (9, 9) is out of valid bounds.` |
| **10** | Reject Already Booked Seat | `2` -> `Bob`, `0`, `0` | Error: `Seat (0, 0) is already booked!` |
| **11** | Book Multiple Seats | `2` -> `David`, `1`, `1`<br>`2` -> `Charlie`, `2`, `2` | David booked at (1, 1) ($150); Charlie at (2, 2) ($200). Persisted to MySQL. |
| **12** | View All Active Bookings | `4` | Formatted table listing Alice (101), David (102), Charlie (103). |
| **13** | Search Booking (Found) | `5` -> `Alice` | Displays Booking ID 101, Row 0, Col 0, Price $150.00. |
| **14** | Search Booking (Not Found) | `5` -> `Zack` | Displays `No bookings found matching "Zack".` |
| **15** | Sort Bookings Alphabetically | `6` | Runs `std::sort`. Displays active bookings sorted: Alice, Charlie, David. |
| **16** | Undo Last Booking (LIFO) | `8` | Pops Charlie's booking (103). Seat (2, 2) freed `[ O ]`. Deleted from MySQL. |
| **17** | Cancel Non-Existent ID | `3` -> `999` | Error: `Booking ID 999 not found.` |
| **18** | Cancel Active Booking | `3` -> `102` | David's booking (102) cancelled. Seat (1, 1) freed `[ O ]`. Deleted from MySQL. |
| **19** | Full Cinema & Queue FIFO | Book all 30 seats -> next book offers waitlist -> cancel a seat -> auto-assigned to 1st waiting customer | Demonstrates `waitlist.push()` and automatic FIFO allocation on cancellation. |
| **20** | Persistence Reload Verification | Exit `9` -> Re-run `./cineseat.exe` -> Option `4` | Reconnects to MySQL. Reloads 1 booking (Alice, ID 101). Restores `seats[0][0]` as `[ X ]`. |

---

## 🎬 10-Minute Scripted Input Stream

You can run this exact PowerShell pipeline to execute the core test suite automatically:

```powershell
@'
1
2
Alice
0
0
2
David
1
1
4
6
5
Alice
8
4
1
9
'@ | .\cineseat.exe
```
