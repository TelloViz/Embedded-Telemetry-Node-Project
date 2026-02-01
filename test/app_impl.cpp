// ============================================================================
// IMPORTANT: This file is kept in sync with firmware/src/app.cpp
// 
// PlatformIO's native test runner only compiles files in the test/ directory.
// Since app.cpp contains the core logic we want to test, we maintain a copy
// here for test compilation. Both files should remain identical.
//
// When updating firmware/src/app.cpp, copy changes to this file:
//   copy ..\firmware\src\app.cpp app_impl.cpp
// ============================================================================

// app.cpp
#include "app.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// Default telemetry period can be set from PlatformIO build flags:
// -D TELEMETRY_DEFAULT_PERIOD_MS=200
#ifndef TELEMETRY_DEFAULT_PERIOD_MS
#define TELEMETRY_DEFAULT_PERIOD_MS 1000
#endif

namespace app
{
    // Heartbeat LED toggle period
    static const uint32_t HEARTBEAT_PERIOD_MS = 2000;

    static void log_status(const app_t *app, uint32_t now_ms)
    {
        static char buffer[128];
        snprintf(buffer, sizeof(buffer),
                 "STATE=%d TIME=%lu TELEMETRY_MS=%lu HEARTBEAT_MS=%lu FAULTS=%lu",
                 (int)app->state,
                 (unsigned long)(now_ms - app->boot_ms),
                 (unsigned long)app->telemetry_period_ms,
                 (unsigned long)HEARTBEAT_PERIOD_MS,
                 (unsigned long)app->fault_count);
        if (app->logger)
            app->logger->log(buffer);
    }

    void app_init(app_t *app, uint32_t now_ms, hal::led::IHalLed* led, hal::time::IHalTime* time, hal::serial::ISerialIo* serial, hal::logging::ILogger* logger)
    {
        memset(app, 0, sizeof(*app));
        app->state = APP_BOOT;
        app->boot_ms = now_ms;
        app->telemetry_period_ms = (uint32_t)TELEMETRY_DEFAULT_PERIOD_MS;
        app->last_telemetry_ms = now_ms;
        app->last_heartbeat_ms = now_ms;
        app->led = led;
        app->time = time;
        app->serial = serial;
        app->logger = logger;

        // Initialize LED
        led->hal_led_init();

        // Transition immediately to IDLE
        app->state = APP_IDLE;
    }

    void app_tick(app_t *app, uint32_t now_ms)
    {
        // Heartbeat LED: do not block, just toggle when due.
        if (app->led_override)
        {
            app->led->hal_led_set(app->led_override_value);
        }
        else
        {
            if ((uint32_t)(now_ms - app->last_heartbeat_ms) >= HEARTBEAT_PERIOD_MS)
            {
                app->last_heartbeat_ms = now_ms;
                app->led->hal_led_toggle();
            }
        }

        // Telemetry: emit a line when due.
        if ((uint32_t)(now_ms - app->last_telemetry_ms) >= app->telemetry_period_ms)
        {
            app->last_telemetry_ms = now_ms;
            log_status(app, now_ms);
        }
    }

    void app_handle_command(app_t *app, const char *line)
    {
        if (app == NULL || line == NULL)
            return;

        // Skip leading whitespace (helps if host sends " LED ON")
        while (*line == ' ' || *line == '\t')
        {
            line++;
        }

        // Ignore empty lines
        if (*line == '\0')
            return;

        // HELP
        if (strcmp(line, "HELP") == 0)
        {
            app->serial->hal_serial_print("OK Commands: HELP STATUS LED ON|OFF|AUTO RATE <ms> ARM DISARM FAULT");
            return;
        }

        // STATUS
        if (strcmp(line, "STATUS") == 0)
        {
            app->serial->hal_serial_print("OK ");
            log_status(app, app->time->hal_millis());
            return;
        }

        // ARM / DISARM
        if (strcmp(line, "ARM") == 0)
        {
            app->state = APP_ARMED;
            app->serial->hal_serial_print("OK ARMED");
            return;
        }

        if (strcmp(line, "DISARM") == 0)
        {
            app->state = APP_IDLE;
            app->serial->hal_serial_print("OK IDLE");
            return;
        }

        // FAULT
        if (strcmp(line, "FAULT") == 0)
        {
            app->fault_count++;
            app->state = APP_FAULT;
            app->serial->hal_serial_print("OK FAULT");
            return;
        }

        // LED commands
        if (strncmp(line, "LED ", 4) == 0)
        {
            const char *arg = line + 4;

            while (*arg == ' ' || *arg == '\t')
            {
                arg++;
            }

            if (strcmp(arg, "ON") == 0)
            {
                app->led_override = true;       // manual mode enabled
                app->led_override_value = true; // manual value
                app->led->hal_led_set(true);
                app->serial->hal_serial_print("OK LED ON");
                return;
            }

            if (strcmp(arg, "OFF") == 0)
            {
                app->led_override = true;        // manual mode enabled
                app->led_override_value = false; // manual value
                app->led->hal_led_set(false);
                app->serial->hal_serial_print("OK LED OFF");
                return;
            }

            if (strcmp(arg, "AUTO") == 0)
            {
                app->led_override = false; // return control to heartbeat
                app->serial->hal_serial_print("OK LED AUTO");
                return;
            }

            app->serial->hal_serial_print("ERR LED expects ON OFF AUTO");
            return;
        }

        // RATE <ms>
        if (strncmp(line, "RATE ", 5) == 0)
        {
            const char *p = line + 5;

            while (*p == ' ' || *p == '\t')
            {
                p++;
            }

            char *end = NULL;
            long ms = strtol(p, &end, 10);

            // Validate parse: must have at least one digit and no trailing junk
            if (end == p)
            {
                app->serial->hal_serial_print("ERR RATE expects an integer");
                return;
            }
            while (*end == ' ' || *end == '\t')
            {
                end++;
            }
            if (*end != '\0')
            {
                app->serial->hal_serial_print("ERR RATE expects only an integer");
                return;
            }

            // Clamp to reasonable bounds for MVP
            if (ms < 10 || ms > 60000)
            {
                app->serial->hal_serial_print("ERR RATE out of range (10..60000)");
                return;
            }

            app->telemetry_period_ms = (uint32_t)ms;
            app->serial->hal_serial_print("OK RATE SET");
            return;
        }

        app->serial->hal_serial_print("ERR Unknown command");
    }

} // namespace app