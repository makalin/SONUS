#pragma once

#include <string>
#include <stdexcept>

namespace sonus {

enum class ErrorCode {
    Success = 0,
    InvalidParameters,
    BufferOverflow,
    DecodeError,
    EncodeError,
    MemoryError,
    AudioError
};

class SonusException : public std::runtime_error {
public:
    SonusException(ErrorCode code, const std::string& message)
        : std::runtime_error(message)
        , m_code(code)
    {}

    ErrorCode code() const { return m_code; }

private:
    ErrorCode m_code;
};

// Logging interface
class Logger {
public:
    enum class Level {
        Debug,
        Info,
        Warning,
        Error
    };

    static void log(Level level, const std::string& message);
    static void setLogLevel(Level level);
    static void setLogFile(const std::string& filename);

private:
    static Level s_logLevel;
    static std::string s_logFile;
};

} // namespace sonus 