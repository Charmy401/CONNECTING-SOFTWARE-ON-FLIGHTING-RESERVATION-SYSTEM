#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <stdexcept>

// Class to represent a Flight
class Flight {
public:
    int flightID;
    std::string origin;
    std::string destination;
    int availableSeats;
    double price;

    Flight(int id, std::string origin, std::string destination, int seats, double price)
        : flightID(id), origin(origin), destination(destination), availableSeats(seats), price(price) {}
    
    // Display flight details
    void display() {
        std::cout << "Flight ID: " << flightID << ", "
                  << "From: " << origin << " To: " << destination << ", "
                  << "Available Seats: " << availableSeats << ", "
                  << "Price: $" << price << std::endl;
    }
};

// Class for the flight database (simulated)
class FlightDatabase {
private:
    std::unordered_map<int, Flight> flights;

public:
    FlightDatabase() {
        // Sample flight data
        flights[101] = Flight(101, "New York", "Los Angeles", 100, 299.99);
        flights[102] = Flight(102, "Chicago", "Miami", 50, 199.99);
        flights[103] = Flight(103, "San Francisco", "London", 200, 799.99);
        flights[104] = Flight(104, "Los Angeles", "Tokyo", 30, 599.99);
    }

    // Retrieve a flight by its ID
    Flight* getFlight(int flightID) {
        if (flights.find(flightID) != flights.end()) {
            return &flights[flightID];
        }
        return nullptr; // Flight not found
    }

    // List all flights
    void listAllFlights() {
        for (const auto& pair : flights) {
            pair.second.display();
        }
    }
};

// Class for the middleware (handles reservation logic)
class FlightReservationMiddleware {
private:
    FlightDatabase& flightDB;

public:
    FlightReservationMiddleware(FlightDatabase& db) : flightDB(db) {}

    // Check if a flight is available and can be booked
    bool checkAvailability(int flightID, int requestedSeats) {
        Flight* flight = flightDB.getFlight(flightID);
        if (flight != nullptr) {
            if (flight->availableSeats >= requestedSeats) {
                return true; // Seats are available
            } else {
                std::cout << "Not enough seats available for Flight ID: " << flightID << std::endl;
                return false;
            }
        }
        std::cout << "Flight ID: " << flightID << " not found." << std::endl;
        return false;
    }

    // Book a flight (update available seats)
    bool bookFlight(int flightID, int requestedSeats) {
        Flight* flight = flightDB.getFlight(flightID);
        if (flight != nullptr) {
            if (checkAvailability(flightID, requestedSeats)) {
                flight->availableSeats -= requestedSeats;
                std::cout << "Successfully booked " << requestedSeats << " seat(s) on Flight ID: " << flightID << std::endl;
                return true;
            }
        }
        return false;
    }

    // Search flights by origin and destination
    void searchFlights(const std::string& origin, const std::string& destination) {
        bool found = false;
        for (const auto& pair : flightDB.flights) {
            if (pair.second.origin == origin && pair.second.destination == destination) {
                pair.second.display();
                found = true;
            }
        }
        if (!found) {
            std::cout << "No flights found for " << origin << " to " << destination << std::endl;
        }
    }
};

// User interface class (simulates user interaction)
class FlightReservationSystem {
private:
    FlightReservationMiddleware& middleware;

public:
    FlightReservationSystem(FlightReservationMiddleware& mw) : middleware(mw) {}

    // Simulate user actions
    void run() {
        int choice;
        while (true) {
            std::cout << "\n==== Flight Reservation System ====" << std::endl;
            std::cout << "1. List All Flights" << std::endl;
            std::cout << "2. Search Flights by Origin & Destination" << std::endl;
            std::cout << "3. Book Flight" << std::endl;
            std::cout << "4. Exit" << std::endl;
            std::cout << "Enter your choice: ";
            std::cin >> choice;

            if (choice == 1) {
                std::cout << "\nAvailable Flights:\n";
                middleware.flightDB.listAllFlights();
            }
            else if (choice == 2) {
                std::string origin, destination;
                std::cout << "\nEnter origin: ";
                std::cin >> origin;
                std::cout << "Enter destination: ";
                std::cin >> destination;
                middleware.searchFlights(origin, destination);
            }
            else if (choice == 3) {
                int flightID, requestedSeats;
                std::cout << "\nEnter Flight ID to book: ";
                std::cin >> flightID;
                std::cout << "Enter number of seats to book: ";
                std::cin >> requestedSeats;
                middleware.bookFlight(flightID, requestedSeats);
            }
            else if (choice == 4) {
                std::cout << "Exiting the system. Thank you!" << std::endl;
                break;
            }
            else {
                std::cout << "Invalid choice. Please try again." << std::endl;
            }
        }
    }
};

int main() {
    // Initialize database and middleware
    FlightDatabase db;
    FlightReservationMiddleware middleware(db);

    // Initialize the system and run
    FlightReservationSystem system(middleware);
    system.run();

    return 0;
}
