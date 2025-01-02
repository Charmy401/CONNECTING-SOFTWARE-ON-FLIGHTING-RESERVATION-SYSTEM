#include <iostream>
#include <queue>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>

// Define message types
enum class MessageType {
    FlightSearch,
    Reservation,
    Payment
};

// Structure to represent a message in the queue
struct Message {
    MessageType type;
    std::string data;
};

// Message Queue class
class MessageQueue {
private:
    std::queue<Message> queue;
    std::mutex mtx;
    std::condition_variable cv;

public:
    // Push a message to the queue
    void push(const Message& msg) {
        std::lock_guard<std::mutex> lock(mtx);
        queue.push(msg);
        cv.notify_all();
    }

    // Pop a message from the queue
    Message pop() {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this]() { return !queue.empty(); });
        
        Message msg = queue.front();
        queue.pop();
        return msg;
    }
};

// Flight search process (worker thread)
void flightSearchWorker(MessageQueue& msgQueue) {
    std::this_thread::sleep_for(std::chrono::seconds(1)); // Simulating search delay
    Message msg = {MessageType::FlightSearch, "Flight search results for New York to Los Angeles"};
    msgQueue.push(msg);
    std::cout << "Flight Search complete, message added to queue\n";
}

// Reservation process (worker thread)
void reservationWorker(MessageQueue& msgQueue) {
    std::this_thread::sleep_for(std::chrono::seconds(2)); // Simulating reservation delay
    Message msg = {MessageType::Reservation, "Reservation for flight AA101 confirmed"};
    msgQueue.push(msg);
    std::cout << "Reservation complete, message added to queue\n";
}

// Payment process (worker thread)
void paymentWorker(MessageQueue& msgQueue) {
    std::this_thread::sleep_for(std::chrono::seconds(1)); // Simulating payment delay
    Message msg = {MessageType::Payment, "Payment of $250 processed for AA101"};
    msgQueue.push(msg);
    std::cout << "Payment complete, message added to queue\n";
}

// Message handling process (consumer thread)
void messageHandler(MessageQueue& msgQueue) {
    while (true) {
        Message msg = msgQueue.pop();
        
        switch (msg.type) {
            case MessageType::FlightSearch:
                std::cout << "Handling flight search message: " << msg.data << "\n";
                break;
            case MessageType::Reservation:
                std::cout << "Handling reservation message: " << msg.data << "\n";
                break;
            case MessageType::Payment:
                std::cout << "Handling payment message: " << msg.data << "\n";
                break;
            default:
                std::cout << "Unknown message type\n";
        }
        
        // For simulation, let's assume we're done when all messages have been handled
        if (msg.data == "Payment of $250 processed for AA101") {
            break;
        }
    }
}

int main() {
    MessageQueue msgQueue;

    // Start worker threads (simulate flight search, reservation, and payment)
    std::thread flightSearchThread(flightSearchWorker, std::ref(msgQueue));
    std::thread reservationThread(reservationWorker, std::ref(msgQueue));
    std::thread paymentThread(paymentWorker, std::ref(msgQueue));

    // Start message handler thread (consume messages from the queue)
    std::thread messageHandlerThread(messageHandler, std::ref(msgQueue));

    // Wait for threads to finish
    flightSearchThread.join();
    reservationThread.join();
    paymentThread.join();
    messageHandlerThread.join();

    std::cout << "Flight reservation system completed successfully.\n";

    return 0;
}
