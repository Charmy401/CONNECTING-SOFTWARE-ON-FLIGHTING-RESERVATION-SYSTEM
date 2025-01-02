#include <iostream>
#include <unordered_map>
#include <list>
#include <string>

class LRUCache {
private:
    int capacity;
    std::list<std::pair<int, std::string>> cache; // Doubly linked list to store key-value pairs
    std::unordered_map<int, std::list<std::pair<int, std::string>>::iterator> map; // Hash map to store key and its corresponding position in the list

public:
    LRUCache(int cap) : capacity(cap) {}

    // Access a flight reservation by flight ID
    std::string get(int flightID) {
        if (map.find(flightID) == map.end()) {
            return "Flight not found"; // Return "not found" if flight ID is not in the cache
        }
        // Move the accessed flight to the front (most recent)
        cache.splice(cache.begin(), cache, map[flightID]);
        return map[flightID]->second; // Return the flight details (in this case, a string)
    }

    // Add or update a flight reservation in the cache
    void put(int flightID, const std::string& flightDetails) {
        if (map.find(flightID) != map.end()) {
            // Flight is already in cache, update it
            cache.splice(cache.begin(), cache, map[flightID]);
            map[flightID]->second = flightDetails;
        } else {
            // If the cache is full, remove the least recently used flight
            if (cache.size() == capacity) {
                // Remove the least recently used (LRU) element
                int oldFlightID = cache.back().first;
                map.erase(oldFlightID);
                cache.pop_back();
            }
            // Insert the new flight reservation at the front
            cache.push_front({flightID, flightDetails});
            map[flightID] = cache.begin();
        }
    }

    // Display the cache (for testing purposes)
    void displayCache() {
        for (const auto& pair : cache) {
            std::cout << "Flight ID: " << pair.first << ", Details: " << pair.second << std::endl;
        }
    }
};

int main() {
    // Create an LRU cache with capacity 3 for flight reservations
    LRUCache flightCache(3);

    // Add some flight reservations to the cache
    flightCache.put(101, "Flight AA101 from New York to Los Angeles");
    flightCache.put(102, "Flight BA102 from London to Paris");
    flightCache.put(103, "Flight AA103 from New York to Miami");

    // Display the cache
    std::cout << "Current cache:" << std::endl;
    flightCache.displayCache();

    // Access a flight reservation (will move it to the front)
    std::cout << "\nAccessing Flight 101: " << flightCache.get(101) << std::endl;

    // Add another flight reservation, which will evict the least recently used one (Flight 102)
    flightCache.put(104, "Flight AA104 from San Francisco to Chicago");

    // Display the updated cache
    std::cout << "\nUpdated cache after adding Flight 104:" << std::endl;
    flightCache.displayCache();

    // Access another flight reservation
    std::cout << "\nAccessing Flight 103: " << flightCache.get(103) << std::endl;

    // Add another flight reservation, which will evict the least recently used one (Flight 103)
    flightCache.put(105, "Flight BA105 from Paris to Tokyo");

    // Final cache display
    std::cout << "\nFinal cache after adding Flight 105:" << std::endl;
    flightCache.displayCache();

    return 0;
}
