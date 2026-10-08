#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <vector>

// Full definition of struct Booking matching syllabus requirements
struct Booking {
    int bookingId;
    std::string customerName;
    std::string movieName;
    int seatRow;
    int seatCol;
    double ticketPrice;
};

/**
 * CineSeat Database Layer (MySQL Integration)
 *
 * Designed to be minimal, robust, and explainable in under 1 minute for a viva.
 * Academic Scope:
 * - Single table: bookings
 * - 4 core operations: connectDatabase, loadBookings, saveBooking, deleteBooking
 */

// Establishes connection to MySQL using local config (db_config.env or defaults)
bool connectDatabase();

// Closes MySQL database connection gracefully
void closeDatabase();

// Loads all existing bookings from MySQL into the vector at startup
bool loadBookings(std::vector<Booking>& list);

// Inserts a newly booked ticket record into MySQL
bool saveBooking(const Booking& b);

// Deletes a cancelled booking record from MySQL by bookingId
bool deleteBooking(int bookingId);

#endif // DATABASE_H
