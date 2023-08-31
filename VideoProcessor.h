#pragma once  // Ensures the header is included only once during compilation

// Include necessary C++ standard library headers
#include <unordered_map>      // For using unordered_map to store operation statuses
#include <thread>             // For using std::thread to create threads
#include <mutex>              // For using std::mutex to ensure thread-safety
#include <condition_variable> // For using std::condition_variable (though not used in this example)

// Declare an enumeration class to represent the status of each operation
enum class OperationStatus { NotStarted, InProgress, Completed, Cancelled };

// Define a struct to represent an Operation
struct Operation {
    int id;  // Unique identifier for an operation
};

// Declare the VideoProcessor class
class VideoProcessor {
public:
    // Declare a member function for initiating a video processing operation
    bool processVideo(Operation& o);

    // Declare a member function for canceling an ongoing operation
    void cancel(Operation &o);

    // Declare a member function for cleaning up an operation
    void cleanup(Operation &o);

private:
    std::mutex mtx;  // Mutex for ensuring thread safety for the `operation_status` map
    std::mutex processing_mtx; // New mutex for ensuring only one operation processes at a time
    // Unordered map to hold the status of operations, keyed by their IDs
    std::unordered_map<int, OperationStatus> operation_status;
};

