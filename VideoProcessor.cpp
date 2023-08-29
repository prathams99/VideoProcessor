#include "VideoProcessor.h"  // Include the header file for VideoProcessor class
#include <iostream>           // For standard input/output operations
#include <chrono>             // For time-related functionalities
#include <iomanip>            // For output formatting (e.g., std::setw)
#include <stdexcept>          // For standard exception classes (e.g., std::runtime_error)

bool VideoProcessor::processVideo(Operation& o) {
    {
        std::unique_lock<std::mutex> lock(mtx);  // Lock the mutex to ensure thread-safety
        if (operation_status[o.id] == OperationStatus::InProgress) {
            throw std::runtime_error("Operation already in progress");  // Throw an exception if the operation is already in progress
        }
        operation_status[o.id] = OperationStatus::InProgress;  // Mark the operation as 'InProgress'
    }  // Unlock the mutex when going out of scope

    std::cout << "Started processing video for operation: " << o.id << std::endl;  // Print a message indicating the start of the operation

    for (int i = 0; i < 5000; i++) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));  // Simulate a time-consuming operation

        // Display the current progress of the operation
        std::cout << "\rOperation " << o.id << " progress: " << std::setw(4) << i << "/5000 ms" << std::flush;

        {
            std::unique_lock<std::mutex> lock(mtx);  // Lock the mutex again for thread-safety
            if (operation_status[o.id] == OperationStatus::Cancelled) {
                std::cout << "\nCancelled operation: " << o.id << std::endl;  // Print a message if the operation was cancelled
                return false;  // Return false to indicate that the operation was cancelled
            }
        }  // Unlock the mutex when going out of scope
    }

    {
        std::unique_lock<std::mutex> lock(mtx);  // Lock the mutex one more time for thread-safety
        operation_status[o.id] = OperationStatus::Completed;  // Mark the operation as 'Completed'
    }  // Unlock the mutex when going out of scope

    std::cout << "\nFinished processing video for operation: " << o.id << std::endl;  // Print a message indicating the completion of the operation

    return true;  // Return true to indicate successful completion
}

void VideoProcessor::cancel(Operation &o) {
    std::unique_lock<std::mutex> lock(mtx);  // Lock the mutex for thread-safety
    if (operation_status.find(o.id) == operation_status.end()) {
        throw std::runtime_error("Operation does not exist");  // Throw an exception if the operation does not exist
    }
    operation_status[o.id] = OperationStatus::Cancelled;  // Mark the operation as 'Cancelled'
}  // Unlock the mutex when going out of scope

void VideoProcessor::cleanup(Operation &o) {
    std::unique_lock<std::mutex> lock(mtx);  // Lock the mutex for thread-safety
    if (operation_status.find(o.id) == operation_status.end()) {
        throw std::runtime_error("Operation does not exist");  // Throw an exception if the operation does not exist
    }
    operation_status.erase(o.id);  // Remove the operation from the map
}  // Unlock the mutex when going out of scope

