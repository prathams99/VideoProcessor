#pragma once

#include <unordered_map>
#include <thread>
#include <mutex>
#include <condition_variable>

enum class OperationStatus { NotStarted, InProgress, Completed, Cancelled };

struct Operation {
    int id;
};

class VideoProcessor {
public:
    bool processVideo(Operation& o);
    void cancel(Operation &o);
    void cleanup(Operation &o);

private:
    std::mutex mtx;
    std::unordered_map<int, OperationStatus> operation_status;
};

