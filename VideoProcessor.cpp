#include "VideoProcessor.h"
#include <iostream>
#include <chrono>
#include <iomanip>

bool VideoProcessor::processVideo(Operation& o) {
    {
        std::unique_lock<std::mutex> lock(mtx);
        if (operation_status[o.id] == OperationStatus::InProgress) {
            // Log: Already in progress
            return false;
        }
        operation_status[o.id] = OperationStatus::InProgress;
    }

    std::cout << "Started processing video for operation: " << o.id << std::endl;

    for (int i = 0; i < 5000; i++) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));

        std::cout << "\rOperation " << o.id << " progress: " << std::setw(4) << i << "/5000 ms" << std::flush;

        std::unique_lock<std::mutex> lock(mtx);
        if (operation_status[o.id] == OperationStatus::Cancelled) {
            std::cout << "\nCancelled operation: " << o.id << std::endl;
            return false;
        }
    }

    {
        std::unique_lock<std::mutex> lock(mtx);
        operation_status[o.id] = OperationStatus::Completed;
    }

    std::cout << "\nFinished processing video for operation: " << o.id << std::endl;
    return true;
}

void VideoProcessor::cancel(Operation &o) {
    std::unique_lock<std::mutex> lock(mtx);
    if (operation_status.find(o.id) != operation_status.end()) {
        operation_status[o.id] = OperationStatus::Cancelled;
    }
    // else Log: Operation doesn't exist
}

void VideoProcessor::cleanup(Operation &o) {
    std::unique_lock<std::mutex> lock(mtx);
    operation_status.erase(o.id);
}

