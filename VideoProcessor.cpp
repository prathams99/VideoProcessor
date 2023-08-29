#include "VideoProcessor.h"  // Include the header file for VideoProcessor class
#include <iostream>           // For console output
#include <chrono>             // For time-related functions
#include <iomanip>            // For formatting output

bool VideoProcessor::processVideo(Operation& o) {
    {
        std::unique_lock<std::mutex> lock(mtx);  // Lock the mutex
        if (operation_status[o.id] == OperationStatus::InProgress) {
            // Log: Already in progress
            return false;  // Return false if this operation is already in progress
        }
        operation_status[o.id] = OperationStatus::InProgress;  // Set operation status to 'InProgress'
    }  // Mutex is unlocked when the lock goes out of scope

    std::cout << "Started processing video for operation: " << o.id << std::endl;  // Notify that the operation started

    for (int i = 0; i < 5000; i++) {  // Simulate video processing for 5000 milliseconds
        std::this_thread::sleep_for(std::chrono::milliseconds(1));  // Sleep for 1 ms

        std::cout << "\rOperation " << o.id << " progress: " << std::setw(4) << i << "/5000 ms" << std::flush;  // Show progress

        std::unique_lock<std::mutex> lock(mtx);  // Lock the mutex again
        if (operation_status[o.id] == OperationStatus::Cancelled) {
            std::cout << "\nCancelled operation: " << o.id << std::endl;  // Notify if the operation is cancelled
            return false;  // Return false if the operation is cancelled
        }
    }  // End of for loop

    {
        std::unique_lock<std::mutex> lock(mtx);  // Lock the mutex
        operation_status[o.id] = OperationStatus::Completed;  // Set the operation status to 'Completed'
    }  // Mutex is unlocked when the lock goes out of scope

    std::cout << "\nFinished processing video for operation: " << o.id << std::endl;  // Notify that the operation is complete
    return true;  // Return true if the operation is successfully completed
}

void VideoProcessor::cancel(Operation &o) {
    std::unique_lock<std::mutex> lock(mtx);  // Lock the mutex
    if (operation_status.find(o.id) != operation_status.end()) {
        operation_status[o.id] = OperationStatus::Cancelled;  // Set the operation status to 'Cancelled' if it exists
    }
    // else Log: Operation doesn't exist
}  // Mutex is unlocked when the lock goes out of scope

void VideoProcessor::cleanup(Operation &o) {
    std::unique_lock<std::mutex> lock(mtx);  // Lock the mutex
    operation_status.erase(o.id);  // Remove the operation status from the unordered_map
}  // Mutex is unlocked when the lock goes out of scope

