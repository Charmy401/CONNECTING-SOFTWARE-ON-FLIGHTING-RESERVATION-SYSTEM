#include <iostream>
#include <vector>
#include <string>
#include <fstream>

class FlightFeedbackSystem {
private:
    struct Feedback {
        std::string customerName;
        std::string feedbackText;
    };
    
    std::vector<Feedback> feedbackList;

public:
    // Method to submit feedback from customers
    void submitFeedback() {
        std::string name;
        std::string feedback;
        
        std::cout << "Enter your name: ";
        std::cin.ignore();  // Clear the input buffer
        std::getline(std::cin, name);
        
        std::cout << "Enter your feedback: ";
        std::getline(std::cin, feedback);
        
        Feedback newFeedback = {name, feedback};
        feedbackList.push_back(newFeedback);
        
        std::cout << "Thank you for your feedback!\n" << std::endl;
    }
    
    // Method to view all feedback
    void viewFeedback() {
        if (feedbackList.empty()) {
            std::cout << "No feedback has been submitted yet.\n" << std::endl;
        } else {
            std::cout << "\nAll Customer Feedback:\n";
            std::cout << "--------------------------------------\n";
            for (const auto& feedback : feedbackList) {
                std::cout << "Customer: " << feedback.customerName << std::endl;
                std::cout << "Feedback: " << feedback.feedbackText << "\n";
                std::cout << "--------------------------------------\n";
            }
        }
    }
    
    // Method to save feedback to a file
    void saveFeedbackToFile() {
        std::ofstream outFile("flight_feedbacks.txt", std::ios::app);
        
        if (!outFile) {
            std::cout << "Error opening file to save feedback.\n" << std::endl;
            return;
        }
        
        for (const auto& feedback : feedbackList) {
            outFile << "Customer: " << feedback.customerName << "\n";
            outFile << "Feedback: " << feedback.feedbackText << "\n";
            outFile << "--------------------------------------\n";
        }
        
        std::cout << "Feedback has been saved!\n" << std::endl;
    }

    // Method to load feedback from a file
    void loadFeedbackFromFile() {
        std::ifstream inFile("flight_feedbacks.txt");
        
        if (!inFile) {
            std::cout << "No previous feedback found.\n" << std::endl;
            return;
        }
        
        std::string name, feedback;
        while (std::getline(inFile, name) && std::getline(inFile, feedback)) {
            Feedback newFeedback = {name.substr(10), feedback.substr(10)};  // Removing "Customer: " and "Feedback: "
            feedbackList.push_back(newFeedback);
        }

        std::cout << "Feedback loaded from file.\n" << std::endl;
    }
};

int main() {
    FlightFeedbackSystem system;
    int choice;

    // Load previous feedback from the file
    system.loadFeedbackFromFile();

    while (true) {
        std::cout << "Flight Reservation System\n";
        std::cout << "1. Submit Feedback\n";
        std::cout << "2. View All Feedback\n";
        std::cout << "3. Save Feedback to File\n";
        std::cout << "4. Exit\n";
        std::cout << "Please select an option (1-4): ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                system.submitFeedback();
                break;
            case 2:
                system.viewFeedback();
                break;
            case 3:
                system.saveFeedbackToFile();
                break;
            case 4:
                std::cout << "Exiting the feedback system. Thank you!\n";
                return 0;
            default:
                std::cout << "Invalid option, please try again.\n";
                break;
        }
    }
}
