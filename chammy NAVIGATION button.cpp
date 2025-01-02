#include <iostream>
#include <string>
#include <vector>

// Flight structure
struct Flight {
    int flightNumber;
    std::string airline;
    std::string destination;
    std::string departureTime;
    float price;
};

// Class representing the Flight Reservation System
class FlightReservationSystem {
private:
    std::vector<Flight> flights;

public:
    // Constructor to initialize some flights
    FlightReservationSystem() {
        flights.push_back({1001, "Delta Airlines", "New York", "2025-01-15 08:00", 350.75});
        flights.push_back({1002, "American Airlines", "Los Angeles", "2025-01-16 10:30", 275.50});
        flights.push_back({1003, "United Airlines", "Chicago", "2025-01-18 15:45", 200.00});
        flights.push_back({1004, "Southwest Airlines", "San Francisco", "2025-01-20 12:00", 150.25});
    }

    // Method to display available flights
    void displayFlights() {
        std::cout << "\nAvailable Flights:\n";
        std::cout << "-------------------------------------------\n";
        for (const auto& flight : flights) {
            std::cout << "Flight Number: " << flight.flightNumber
                      << ", Airline: " << flight.airline
                      << ", Destination: " << flight.destination
                      << ", Departure: " << flight.departureTime
                      << ", Price: $" << flight.price << "\n";
        }
        std::cout << "-------------------------------------------\n";
    }

    // Method to make a reservation
    void makeReservation() {
        int selectedFlight;
        std::cout << "Enter the Flight Number you want to reserve: ";
        std::cin >> selectedFlight;

        // Search for the selected flight
        bool flightFound = false;
        Flight selectedFlightDetails;
        for (const auto& flight : flights) {
            if (flight.flightNumber == selectedFlight) {
                selectedFlightDetails = flight;
                flightFound = true;
                break;
            }
        }

        if (!flightFound) {
            std::cout << "Invalid flight number. Please try again.\n";
            return;
        }

        // Get passenger details
        std::string passengerName;
        std::cout << "Enter your name: ";
        std::cin.ignore();  // Clear the input buffer
        std::getline(std::cin, passengerName);

        // Display confirmation
        std::cout << "\nReservation Confirmed!\n";
        std::cout << "----------------------------\n";
        std::cout << "Passenger: " << passengerName << "\n";
        std::cout << "Flight Number: " << selectedFlightDetails.flightNumber
                  << ", Airline: " << selectedFlightDetails.airline
                  << ", Destination: " << selectedFlightDetails.destination
                  << ", Departure: " << selectedFlightDetails.departureTime
                  << ", Price: $" << selectedFlightDetails.price << "\n";
        std::cout << "----------------------------\n";
    }
};

// Main function to display navigation
int main() {
    FlightReservationSystem system;
    int choice;

    std::cout << "Welcome to the Flight Reservation System\n";
    while (true) {
        std::cout << "\nNavigation Menu:\n";
        std::cout << "1. View Available Flights\n";
        std::cout << "2. Make a Reservation\n";
        std::cout << "3. Exit\n";
        std::cout << "Please select an option (1-3): ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                system.displayFlights();
                break;
            case 2:
                system.makeReservation();
                break;
            case 3:
                std::cout << "Exiting the system. Goodbye!\n";
                return 0;
            default:
                std::cout << "Invalid option, please try again.\n";
                break;
        }
    }
}
