#include "VideoProcessor.h"
#include <thread>

int main() {
    VideoProcessor processor;
    std::thread threads[4];
    Operation operations[4] = {{1}, {2}, {3}, {4}};

    for (int i = 0; i < 4; ++i) {
        threads[i] = std::thread([&processor, &operations, i]() {
            processor.processVideo(operations[i]);
        });
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    processor.cancel(operations[0]);
    processor.cancel(operations[2]);

    for (int i = 0; i < 4; ++i) {
        threads[i].join();
    }

    return 0;
}

