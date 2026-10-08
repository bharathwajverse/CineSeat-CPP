-- CineSeat Database Schema
-- Academic Mini Project: Single Table Design for MySQL

CREATE DATABASE IF NOT EXISTS cinedb;
USE cinedb;

-- Drop table if exists for clean re-runs
DROP TABLE IF EXISTS bookings;

-- Table: bookings
-- Matches the C++ struct Booking definition exactly
CREATE TABLE bookings (
    booking_id INT PRIMARY KEY,
    customer_name VARCHAR(100) NOT NULL,
    movie_name VARCHAR(100) NOT NULL,
    seat_row INT NOT NULL,
    seat_col INT NOT NULL,
    ticket_price DECIMAL(8, 2) NOT NULL,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- Demonstration Sample Inserts
INSERT INTO bookings (booking_id, customer_name, movie_name, seat_row, seat_col, ticket_price) VALUES
(101, 'Alice Smith', 'Interstellar', 0, 0, 150.00),
(102, 'Bob Jones', 'Interstellar', 1, 2, 180.00),
(103, 'Charlie Brown', 'Interstellar', 4, 5, 250.00);

-- Query: Select all active bookings
SELECT * FROM bookings ORDER BY customer_name ASC;

-- Query: Delete booking by ID (Cancellation)
-- DELETE FROM bookings WHERE booking_id = 101;
