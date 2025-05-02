#pragma once

#include <string>
#include <chrono>
#include <map>
#include <mutex>

namespace sonus {

class PerfMonitor {
public:
    static PerfMonitor& getInstance();
    
    // Start measuring a named operation
    void startOperation(const std::string& name);
    
    // Stop measuring a named operation
    void stopOperation(const std::string& name);
    
    // Get statistics for an operation
    struct OperationStats {
        double minTime = 0.0;
        double maxTime = 0.0;
        double avgTime = 0.0;
        size_t count = 0;
    };
    
    OperationStats getStats(const std::string& name) const;
    
    // Reset all statistics
    void reset();
    
    // Print statistics to log
    void printStats() const;
    
private:
    PerfMonitor() = default;
    PerfMonitor(const PerfMonitor&) = delete;
    PerfMonitor& operator=(const PerfMonitor&) = delete;
    
    struct OperationData {
        std::chrono::high_resolution_clock::time_point startTime;
        OperationStats stats;
    };
    
    std::map<std::string, OperationData> m_operations;
    mutable std::mutex m_mutex;
};

// RAII wrapper for measuring operations
class ScopedOperation {
public:
    ScopedOperation(const std::string& name)
        : m_name(name)
    {
        PerfMonitor::getInstance().startOperation(name);
    }
    
    ~ScopedOperation() {
        PerfMonitor::getInstance().stopOperation(m_name);
    }
    
private:
    std::string m_name;
};

} // namespace sonus 