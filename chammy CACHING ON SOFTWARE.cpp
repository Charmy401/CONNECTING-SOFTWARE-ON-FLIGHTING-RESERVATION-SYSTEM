#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <ctime>


struct Flight {
    std::string flightNumber;
    std::string origin;
    std::string destination;
    std::string date;
    double price;
    
    bool operator==(const Flight& other) const {
        return flightNumber == other.flightNumber && origin == other.origin && destination == other.destination;
    }
};


struct FlightHash {
    std::size_t operator()(const Flight& flight) const {
        std::hash<std::string> hash_fn;
        return hash_fn(flight.flightNumber) ^ hash_fn(flight.origin) ^ hash_fn(flight.destination);
    }
};


class FlightCache {
private:
    std::unordered_map<Flight, std::vector<Flight>, FlightHash> cache;

public:
    
    bool isCached(const Flight& query) {
        return cache.find(query) != cache.end();
    }

    
    std::vector<Flight> getCache(const Flight& query) {
        return cache[query];
    }

    
    void addToCache(const Flight& query, const std::vector<Flight>& availableFlights) {
        cache[query] = availableFlights;
    }

    
    void printCache() {
        for (const auto& pair : cache) {
            std::cout << "Cache for Flight: " << pair.first.flightNumber << "\n";
            for (const auto& flight : pair.second) {
                std::cout << "Flight Number: " << flight.flightNumber << ", From: " << flight.origin << " To: " << flight.destination << ", Price: $" << flight.price << "\n";
            }
        }
    }
};


std::vector<Flight> searchAvailableFlights(const Flight& query) {
    std::cout << "Searching flights from " << query.origin << " to " << query.destination << " on " << query.date << "...\n";
    
    
    std::vector<Flight> flights = {
        {"AA101", query.origin, query.destination, query.date, 250.0},
        {"AA102", query.origin, query.destination, query.date, 300.0},
        {"AA103", query.origin, query.destination, query.date, 200.0}
    };
    

    std::this_thread::sleep_for(std::chrono::seconds(2));
    
    return flights;
}

int main() {
    FlightCache cache;

    
    Flight query1 = {"AA101", "New York", "Los Angeles", "2025-01-15"};
    Flight query2 = {"AA101", "New York", "Los Angeles", "2025-01-15"};


    if (cache.isCached(query1)) {
        std::cout << "Cache hit! Retrieving data from cache.\n";
        auto cachedFlights = cache.getCache(query1);
        for (const auto& flight : cachedFlights) {
            std::cout << "Flight Number: " << flight.flightNumber << ", From: " << flight.origin << " To: " << flight.destination << ", Price: $" << flight.price << "\n";
        }
    } else {
        std::cout << "Cache miss! Searching for flights...\n";
        auto availableFlights = searchAvailableFlights(query1);
        cache.addToCache(query1, availableFlights);
        
        for (const auto& flight : availableFlights) {
            std::cout << "Flight Number: " << flight.flightNumber << ", From: " << flight.origin << " To: " << flight.destination << ", Price: $" << flight.price << "\n";
        }
    }

    
    if (cache.isCached(query2)) {
        std::cout << "Cache hit! Retrieving data from cache for query2.\n";
        auto cachedFlights = cache.getCache(query2);
        for (const auto& flight : cachedFlights) {
            std::cout << "Flight Number: " << flight.flightNumber << ", From: " << flight.origin << " To: " << flight.destination << ", Price: $" << flight.price << "\n";
        }
    }

    
    cache.printCache();
    
    return 0;
}
