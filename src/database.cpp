#include "database.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <mysql.h>


// Internal MySQL connection pointer
static MYSQL* conn = nullptr;

// Default connection parameters
static std::string db_host = "localhost";
static std::string db_user = "root";
static std::string db_pass = "";
static std::string db_name = "cinema_db";
static unsigned int db_port = 3306;

// Helper to safely load key-value pairs from db_config.env
static void loadConfig() {
    std::ifstream file("db_config.env");
    if (!file.is_open()) return; // Keep defaults if file does not exist

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;
        size_t eqPos = line.find('=');
        if (eqPos != std::string::npos) {
            std::string key = line.substr(0, eqPos);
            std::string val = line.substr(eqPos + 1);
            if (key == "DB_HOST") db_host = val;
            else if (key == "DB_USER") db_user = val;
            else if (key == "DB_PASS") db_pass = val;
            else if (key == "DB_NAME") db_name = val;
            else if (key == "DB_PORT") {
                try { db_port = std::stoul(val); } catch (...) {}
            }
        }
    }
}

// 1. connectDatabase: Initialize MySQL handle and connect
bool connectDatabase() {
    loadConfig();

    conn = mysql_init(nullptr);
    if (!conn) {
        std::cerr << "[DB Error] mysql_init failed.\n";
        return false;
    }

    if (!mysql_real_connect(conn, db_host.c_str(), db_user.c_str(), db_pass.c_str(),
                            db_name.c_str(), db_port, nullptr, 0)) {
        std::cerr << "[DB Warning] Could not connect to MySQL: " << mysql_error(conn) << "\n";
        std::cerr << "[DB Note] Running in local offline mode.\n";
        mysql_close(conn);
        conn = nullptr;
        return false;
    }

    std::cout << "[DB Info] Connected to MySQL (" << db_name << " on " << db_host << ").\n";
    return true;
}

// Graceful cleanup
void closeDatabase() {
    if (conn) {
        mysql_close(conn);
        conn = nullptr;
    }
}

// 2. loadBookings: SELECT query populating vector<Booking>
bool loadBookings(std::vector<Booking>& list) {
    if (!conn) return false;

    const char* query = "SELECT booking_id, customer_name, movie_name, seat_row, seat_col, ticket_price FROM bookings;";
    if (mysql_query(conn, query)) {
        std::cerr << "[DB Error] Query failed: " << mysql_error(conn) << "\n";
        return false;
    }

    MYSQL_RES* res = mysql_store_result(conn);
    if (!res) return false;

    MYSQL_ROW row;
    while ((row = mysql_fetch_row(res))) {
        Booking b;
        b.bookingId    = std::stoi(row[0]);
        b.customerName = row[1] ? row[1] : "";
        b.movieName    = row[2] ? row[2] : "";
        b.seatRow      = std::stoi(row[3]);
        b.seatCol      = std::stoi(row[4]);
        b.ticketPrice  = std::stod(row[5]);
        list.push_back(b);
    }

    mysql_free_result(res);
    std::cout << "[DB Info] Loaded " << list.size() << " bookings from MySQL.\n";
    return true;
}

// 3. saveBooking: INSERT query for confirmed tickets
bool saveBooking(const Booking& b) {
    if (!conn) return false;

    std::ostringstream ss;
    ss << "INSERT INTO bookings (booking_id, customer_name, movie_name, seat_row, seat_col, ticket_price) "
       << "VALUES ("
       << b.bookingId << ", '"
       << b.customerName << "', '"
       << b.movieName << "', "
       << b.seatRow << ", "
       << b.seatCol << ", "
       << b.ticketPrice << ");";

    std::string query = ss.str();
    if (mysql_query(conn, query.c_str())) {
        std::cerr << "[DB Error] Insert failed: " << mysql_error(conn) << "\n";
        return false;
    }
    return true;
}

// 4. deleteBooking: DELETE query when ticket is cancelled or undone
bool deleteBooking(int bookingId) {
    if (!conn) return false;

    std::ostringstream ss;
    ss << "DELETE FROM bookings WHERE booking_id = " << bookingId << ";";

    std::string query = ss.str();
    if (mysql_query(conn, query.c_str())) {
        std::cerr << "[DB Error] Delete failed: " << mysql_error(conn) << "\n";
        return false;
    }
    return true;
}
