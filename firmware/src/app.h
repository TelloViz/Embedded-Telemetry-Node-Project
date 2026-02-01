// app.h
#pragma once
#include <stdint.h>
#include <stdbool.h>

#include "hal/led/hal_led.h"
#include "hal/time/hal_time.h"
#include "hal/serial/serial_io.h"
#include "hal/logging/logging.h"

namespace app
{
    typedef enum
    {
        APP_BOOT = 0,
        APP_IDLE,
        APP_ARMED,
        APP_FAULT
    } app_state_t;

    typedef struct
    {
        app_state_t state;

        bool led_override;            // true = manual LED control
        bool led_override_value;      // only meaningful when led_override == true
        uint32_t telemetry_period_ms; // telemetry send period
        uint32_t last_heartbeat_ms;   // last heartbeat time
        uint32_t last_telemetry_ms;   // last telemetry time
        uint32_t boot_ms;             // boot time in ms
        uint32_t fault_count;         // number of faults occurred

        // Injected HAL interfaces
        hal::led::IHalLed *led;
        hal::time::IHalTime *time;
        hal::serial::ISerialIo *serial;
        hal::logging::ILogger *logger;
    } app_t;

    void app_init(app_t *app, uint32_t now_ms, hal::led::IHalLed* led, hal::time::IHalTime* time, hal::serial::ISerialIo* serial, hal::logging::ILogger* logger);
    void app_tick(app_t *app, uint32_t now_ms);
    void app_handle_command(app_t *app, const char *line);

} // namespace app