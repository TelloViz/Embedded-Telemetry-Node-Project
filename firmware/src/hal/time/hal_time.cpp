// hal/time/hal_time.cpp
#include "hal/time/hal_time.h"

#include <Arduino.h>

namespace hal::time
{
    uint32_t hal_millis(void)
    {
        return (uint32_t)millis();
    }
} // namespace hal::time