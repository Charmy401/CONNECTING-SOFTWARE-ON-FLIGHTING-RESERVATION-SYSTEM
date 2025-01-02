#include <iostream>
#include <vector>
#include <string>
#include <fstream>

class CustomerFeedbackSystem {
private:
    struct Feedback {
        std::string customerName;
        std::string feedbackText;
    };
    
    std::vector<Feedback> feedbackList;

public:
    // Method to submit feedback
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
        
        std::cout << "Thank you for your feedback!" << std::endl;
    }
    
    // Method to view all feedback
    void viewFeedback() {
        if (feedbackList.empty()) {
            std::cout << "No feedback has been submitted yet." << std::endl;
        } else {
            std::cout << "\nCustomer Feedback:\n";
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
        std::ofstream outFile("feedbacks.txt", std::ios::app);
        
        if (!outFile) {
            std::cout << "Error opening file to save feedback." << std::endl;
            return;
        }
        
        for (const auto& feedback : feedbackList) {
            outFile << "Customer: " << feedback.customerName << "\n";
            outFile << "Feedback: " << feedback.feedbackText << "\n";
            outFile << "--------------------------------------\n";
        }
        
        std::cout << "Feedback has been saved!" << std::endl;
    }
};

int main() {
    CustomerFeedbackSystem system;
    int choice;

    std::cout << "Welcome to the Flight Reservation System\n";
    
    while (true) {
        std::cout << "\nCustomer Feedback Section:\n";
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
