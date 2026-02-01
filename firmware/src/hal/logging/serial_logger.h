// serial_logger.h
#pragma once
#include "hal/logging/logging.h"

namespace hal::logging
{
    class HalSerialLogger : public ILogger
    {
    public:
        void log(const char* message) override
        {
            if (message)
            {
                Serial.println(message);
            }
        }
    };

} // namespace hal::logging
