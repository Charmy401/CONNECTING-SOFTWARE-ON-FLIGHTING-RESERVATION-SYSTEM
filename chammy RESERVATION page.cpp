#include <iostream>
#include <vector>
#include <string>


struct Flight {
    int flightNumber;
    std::string airline;
    std::string destination;
    std::string departureTime;
    float price;
};


struct Passenger {
    std::string name;
    std::string contactNumber;
    std::string email;
};


class FlightReservationSystem {
private:
    std::vector<Flight> flights;

public:
    
    FlightReservationSystem() {
        flights.push_back({1001, "Delta Airlines", "New York", "2025-01-15 08:00", 350.75});
        flights.push_back({1002, "American Airlines", "Los Angeles", "2025-01-16 10:30", 275.50});
        flights.push_back({1003, "United Airlines", "Chicago", "2025-01-18 15:45", 200.00});
        flights.push_back({1004, "Southwest Airlines", "San Francisco", "2025-01-20 12:00", 150.25});
    }

    
    void displayFlights() {
        std::cout << "Available Flights:\n";
        std::cout << "-------------------------------------------\n";
        for (size_t i = 0; i < flights.size(); ++i) {
            std::cout << "Flight Number: " << flights[i].flightNumber
                      << ", Airline: " << flights[i].airline
                      << ", Destination: " << flights[i].destination
                      << ", Departure: " << flights[i].departureTime
                      << ", Price: $" << flights[i].price << "\n";
        }
        std::cout << "-------------------------------------------\n";
    }

    
    void makeReservation() {
        displayFlights();

        int selectedFlight;
        std::cout << "Enter the Flight Number you want to reserve: ";
        std::cin >> selectedFlight;

        
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
            std::cout << "Invalid flight number, please try again.\n";
            return;
        }

        
        Passenger passenger;
        std::cout << "Enter your name: ";
        std::cin.ignore(); 
        std::getline(std::cin, passenger.name);

        std::cout << "Enter your contact number: ";
        std::getline(std::cin, passenger.contactNumber);

        std::cout << "Enter your email: ";
        std::getline(std::cin, passenger.email);


        std::cout << "\nReservation Successful!\n";
        std::cout << "-------------------------------------------\n";
        std::cout << "Passenger Name: " << passenger.name << "\n";
        std::cout << "Flight Number: " << selectedFlightDetails.flightNumber
                  << ", Airline: " << selectedFlightDetails.airline
                  << ", Destination: " << selectedFlightDetails.destination
                  << ", Departure: " << selectedFlightDetails.departureTime
                  << ", Price: $" << selectedFlightDetails.price << "\n";
        std::cout << "Contact Number: " << passenger.contactNumber << "\n";
        std::cout << "Email: " << passenger.email << "\n";
        std::cout << "-------------------------------------------\n";
    }
};

int main() {
    FlightReservationSystem system;

    std::cout << "Welcome to the Flight Reservation System\n";
    std::cout << "-------------------------------------------\n";
    
    while (true) {
        std::cout << "\nMenu:\n";
        std::cout << "1. View Available Flights\n";
        std::cout << "2. Make a Reservation\n";
        std::cout << "3. Exit\n";
        std::cout << "Please select an option (1-3): ";

        int option;
        std::cin >> option;

        switch (option) {
            case 1:
                system.displayFlights();
                break;
            case 2:
                system.makeReservation();
                break;
            case 3:
                std::cout << "Thank you for using the Flight Reservation System. Goodbye!\n";
                return 0;
            default:
                std::cout << "Invalid option, please try again.\n";
        }
    }

    return 0;
}
