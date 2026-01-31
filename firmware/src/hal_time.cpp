// hal_time.cpp
#include "hal_time.h"

#include <Arduino.h>


uint32_t hal_millis(void) {
    return (uint32_t)millis();
}