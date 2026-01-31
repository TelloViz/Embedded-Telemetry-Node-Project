// hal_time.h
#pragma once
#include <stdint.h>

namespace hal::time {
// Monotonic milliseconds since boot.
uint32_t hal_millis(void);
} // namespace hal::time