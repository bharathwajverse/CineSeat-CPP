-- CineSeat Database Schema
-- Database: cinema_db
-- Table: bookings

CREATE DATABASE IF NOT EXISTS cinema_db;
USE cinema_db;

DROP TABLE IF EXISTS bookings;

CREATE TABLE bookings (
    booking_id INT PRIMARY KEY,
    customer_name VARCHAR(100) NOT NULL,
    movie_name VARCHAR(100) NOT NULL,
    seat_row INT NOT NULL,
    seat_col INT NOT NULL,
    ticket_price DOUBLE NOT NULL
);
