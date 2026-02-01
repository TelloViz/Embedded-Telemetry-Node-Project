#pragma once

namespace hal::logging {
class ILogger {
public:
    virtual ~ILogger() = default;
    virtual void log(const char* message) = 0;
};
} // namespace hal::logging