#include "VideoProcessor.h"  // Include the VideoProcessor header to use its functionality
#include <thread>             // Include the thread library to use std::thread for threading

int main() {  // Main function
    VideoProcessor processor;  // Create an instance of the VideoProcessor class

    std::thread threads[4];  // Declare an array of 4 threads
    Operation operations[4] = {{1}, {2}, {3}, {4}};  // Declare and initialize an array of 4 operations

    // Loop to spawn threads to run the video processing function
    for (int i = 0; i < 4; ++i) {
        threads[i] = std::thread([&processor, &operations, i]() {  // Capture the processor and operations by reference, and i by value
            processor.processVideo(operations[i]);  // Invoke the processVideo function on each operation
        });
    }

    // Sleep the current (main) thread for 100 milliseconds
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    processor.cancel(operations[0]);  // Cancel the operation with ID 1
    processor.cancel(operations[2]);  // Cancel the operation with ID 3

    // Loop to join all threads back to the main thread
    for (int i = 0; i < 4; ++i) {
        threads[i].join();  // Wait for each thread to complete its task
    }

    return 0;  // Exit the program
}

