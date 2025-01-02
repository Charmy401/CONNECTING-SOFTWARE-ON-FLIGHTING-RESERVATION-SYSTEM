#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <vector>

#define PORT 8080
#define MAX_CLIENTS 5

// Sample flight data
struct Flight {
    std::string flightNumber;
    std::string destination;
    float price;
};

class FlightReservationServer {
public:
    void start() {
        int serverSocket, clientSocket;
        struct sockaddr_in serverAddr, clientAddr;
        socklen_t addrSize;

        // Sample flight data
        std::vector<Flight> flights = {
            {"FL100", "New York", 250.50},
            {"FL101", "Los Angeles", 300.75},
            {"FL102", "Chicago", 180.00}
        };

        // Creating socket
        serverSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (serverSocket < 0) {
            std::cerr << "Socket creation failed!" << std::endl;
            return;
        }

        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(PORT);
        serverAddr.sin_addr.s_addr = INADDR_ANY;

        // Binding socket
        if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
            std::cerr << "Binding failed!" << std::endl;
            return;
        }

        // Listening for incoming connections
        if (listen(serverSocket, MAX_CLIENTS) == 0) {
            std::cout << "Server listening on port " << PORT << std::endl;
        } else {
            std::cerr << "Listening failed!" << std::endl;
            return;
        }

        addrSize = sizeof(clientAddr);
        while (true) {
            // Accept client connection
            clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &addrSize);
            if (clientSocket < 0) {
                std::cerr << "Connection failed!" << std::endl;
                continue;
            }

            std::cout << "Client connected!" << std::endl;

            // Receive flight reservation request
            char buffer[1024] = {0};
            read(clientSocket, buffer, sizeof(buffer));

            // Handle flight reservation request
            if (strcmp(buffer, "view_flights") == 0) {
                // Send flight details to client
                std::string flightDetails = "Available Flights:\n";
                for (const auto& flight : flights) {
                    flightDetails += "Flight Number: " + flight.flightNumber +
                                     ", Destination: " + flight.destination +
                                     ", Price: $" + std::to_string(flight.price) + "\n";
                }

                send(clientSocket, flightDetails.c_str(), flightDetails.length(), 0);
            } else {
                std::string response = "Invalid request.";
                send(clientSocket, response.c_str(), response.length(), 0);
            }

            close(clientSocket);
            std::cout << "Client disconnected!" << std::endl;
        }

        close(serverSocket);
    }
};

int main() {
    FlightReservationServer server;
    server.start();
    return 0;
}
