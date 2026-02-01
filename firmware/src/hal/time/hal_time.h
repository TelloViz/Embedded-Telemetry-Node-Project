// hal_time.h
#pragma once
#include <stdint.h>

namespace hal::time
{
    class IHalTime {
        public:
        virtual ~IHalTime() = default;
        virtual uint32_t hal_millis() = 0;
    };

    class HalTime : public IHalTime {
    public:
        uint32_t hal_millis() override; // Get current time in milliseconds
    };

} // namespace hal::time