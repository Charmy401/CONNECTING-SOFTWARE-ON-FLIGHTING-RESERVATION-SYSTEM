#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <stdexcept>

// User class representing a system user (admin or customer)
class User {
public:
    std::string username;
    std::string password;
    std::string role; // "admin" or "customer"

    User(std::string username, std::string password, std::string role) 
        : username(username), password(password), role(role) {}

    bool checkPassword(const std::string& passwordInput) {
        return password == passwordInput;
    }
};

// Simple User Authentication and Authorization System
class AuthSystem {
private:
    std::unordered_map<std::string, User> users;

public:
    AuthSystem() {
        // Pre-populate the system with users (admin and customer)
        users["admin"] = User("admin", "admin123", "admin");
        users["customer1"] = User("customer1", "customer123", "customer");
        users["customer2"] = User("customer2", "customer123", "customer");
    }

    // Authenticate a user by username and password
    User* authenticate(const std::string& username, const std::string& password) {
        if (users.find(username) != users.end() && users[username].checkPassword(password)) {
            return &users[username];
        }
        return nullptr; // Invalid credentials
    }
};

// Class for the flight reservation system
class FlightReservationSystem {
private:
    AuthSystem& authSystem;
    User* loggedInUser = nullptr;

public:
    FlightReservationSystem(AuthSystem& authSys) : authSystem(authSys) {}

    // Login method
    bool login(const std::string& username, const std::string& password) {
        loggedInUser = authSystem.authenticate(username, password);
        return loggedInUser != nullptr;
    }

    // Logout method
    void logout() {
        loggedInUser = nullptr;
        std::cout << "Logged out successfully!" << std::endl;
    }

    // Check if the current user is an admin
    bool isAdmin() {
        return loggedInUser && loggedInUser->role == "admin";
    }

    // Function available only for admins
    void manageFlights() {
        if (!isAdmin()) {
            std::cout << "You do not have permission to manage flights." << std::endl;
            return;
        }
        std::cout << "Managing flights... (only accessible by admins)" << std::endl;
    }

    // Function available for both customers and admins
    void searchFlights() {
        std::cout << "Searching for available flights..." << std::endl;
    }

    // Function available only for customers
    void bookFlight() {
        if (isAdmin()) {
            std::cout << "Admins cannot book flights." << std::endl;
            return;
        }
        std::cout << "Booking a flight... (only accessible by customers)" << std::endl;
    }

    // Function to display
