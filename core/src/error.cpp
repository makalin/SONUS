#include "sonus/error.hpp"
#include <fstream>
#include <ctime>
#include <iomanip>
#include <mutex>

namespace sonus {

Logger::Level Logger::s_logLevel = Logger::Level::Info;
std::string Logger::s_logFile;

void Logger::setLogLevel(Level level) {
    s_logLevel = level;
}

void Logger::setLogFile(const std::string& filename) {
    s_logFile = filename;
}

void Logger::log(Level level, const std::string& message) {
    if (level < s_logLevel) return;

    static std::mutex logMutex;
    std::lock_guard<std::mutex> lock(logMutex);

    const char* levelStr = "UNKNOWN";
    switch (level) {
        case Level::Debug:   levelStr = "DEBUG"; break;
        case Level::Info:    levelStr = "INFO"; break;
        case Level::Warning: levelStr = "WARNING"; break;
        case Level::Error:   levelStr = "ERROR"; break;
    }

    auto now = std::time(nullptr);
    auto tm = std::localtime(&now);
    
    std::stringstream ss;
    ss << std::put_time(tm, "%Y-%m-%d %H:%M:%S") << " [" << levelStr << "] " << message << std::endl;

    if (!s_logFile.empty()) {
        std::ofstream logFile(s_logFile, std::ios::app);
        if (logFile.is_open()) {
            logFile << ss.str();
        }
    } else {
        std::cerr << ss.str();
    }
}

} // namespace sonus 