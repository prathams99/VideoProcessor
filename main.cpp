#include "VideoProcessor.h"  // Include the VideoProcessor class definition
#include <iostream>           // Include for I/O operations
#include <thread>             // Include for std::thread
#include <stdexcept>          // Include for std::runtime_error
#include <future>             // Include for std::promise and std::future
#include <mutex>              // Include for std::mutex and std::lock_guard

int main() {
    std::promise<void> exceptionOccurred;  // Declare a promise for exception handling
    std::future<void> futureObj = exceptionOccurred.get_future();  // Obtain future from the promise
    std::mutex exceptionMutex;  // Mutex for synchronizing access to the promise

    try {
        VideoProcessor processor;  // Create a VideoProcessor object
        std::thread threads[4];  // Declare an array of 4 std::thread objects
        Operation operations[4] = {{1}, {2}, {3}, {4}};  // Declare an array of 4 Operation objects with IDs

        // Launch 4 threads
        for (int i = 0; i < 4; ++i) {
            threads[i] = std::thread([&processor, &operations, i, &exceptionOccurred, &exceptionMutex, &futureObj]() {
                try {
                    // Try to process the video and throw an exception if it fails
                    if (!processor.processVideo(operations[i])) {
                        throw std::runtime_error("Error: Unable to process video for operation " + std::to_string(i));
                    }
                } catch (...) {
                    std::lock_guard<std::mutex> lock(exceptionMutex);  // Lock the mutex
                    // If an exception has not already been set, set it
                    if(futureObj.wait_for(std::chrono::seconds(0)) != std::future_status::ready) {
                        exceptionOccurred.set_exception(std::current_exception());
                    }
                }
            });
        }

        // Wait up to 200ms for any exceptions to be thrown
        if(futureObj.wait_for(std::chrono::milliseconds(200)) == std::future_status::ready) {
            futureObj.get();  // Retrieve and rethrow any caught exceptions
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));  // Sleep the main thread for 100ms

        processor.cancel(operations[0]);  // Cancel operation with ID 1
        processor.cancel(operations[2]);  // Cancel operation with ID 3

        // Wait for all threads to complete
        for (int i = 0; i < 4; ++i) {
            threads[i].join();
        }

    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;  // Print any caught exceptions
        return 1;  // Return 1 indicating program ended due to an error
    }
    return 0;  // Return 0 indicating program ended successfully
}

