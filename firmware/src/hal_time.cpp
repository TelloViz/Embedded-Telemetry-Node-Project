// hal_time.cpp
#include <Arduino.h>
#include "hal_time.h"

uint32_t hal_millis(void) {
    return (uint32_t)millis();
}