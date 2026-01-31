// app.cpp
#include "app.h"

#include <Arduino.h>
#include <string.h>
#include <stdlib.h>

#include "hal/led/hal_led.h"
#include "hal/time/hal_time.h"

// Default telemetry period can be set from PlatformIO build flags:
// -D TELEMETRY_DEFAULT_PERIOD_MS=200
#ifndef TELEMETRY_DEFAULT_PERIOD_MS
#define TELEMETRY_DEFAULT_PERIOD_MS 1000
#endif

// Heartbeat LED toggle period
static const uint32_t HEARTBEAT_PERIOD_MS = 2000;

static void print_status(const app_t *app, uint32_t now_ms)
{
    Serial.print("STATE=");
    Serial.print((int)app->state);
    Serial.print(" ");
    Serial.print(now_ms - app->boot_ms);
    Serial.print(" TELEMETRY_MS=");
    Serial.print(app->telemetry_period_ms);
    Serial.print(" HEARTBEAT_MS=");
    Serial.print(HEARTBEAT_PERIOD_MS);
    Serial.print(" FAULTS=");
    Serial.println(app->fault_count);
}

void app_init(app_t *app, uint32_t now_ms)
{
    memset(app, 0, sizeof(*app));
    app->state = APP_BOOT;
    app->boot_ms = now_ms;
    app->telemetry_period_ms = (uint32_t)TELEMETRY_DEFAULT_PERIOD_MS;
    app->last_telemetry_ms = now_ms;
    app->last_heartbeat_ms = now_ms;

    // Transition immediately to IDLE
    app->state = APP_IDLE;
}

void app_tick(app_t *app, uint32_t now_ms)
{
    // Heartbeat LED: do not block, just toggle when due.
    if (app->led_override)
    {
        hal_led_set(app->led_override_value);
    }
    else
    {
        if ((uint32_t)(now_ms - app->last_heartbeat_ms) >= HEARTBEAT_PERIOD_MS)
        {
            app->last_heartbeat_ms = now_ms;
            hal_led_toggle();
        }
    }

    // Telemetry: emit a line when due.
    if ((uint32_t)(now_ms - app->last_telemetry_ms) >= app->telemetry_period_ms)
    {
        app->last_telemetry_ms = now_ms;
        Serial.print("TEL ");
        print_status(app, now_ms);
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
        Serial.println("OK Commands: HELP STATUS LED ON|OFF|AUTO RATE <ms> ARM DISARM FAULT");
        return;
    }

    // STATUS
    if (strcmp(line, "STATUS") == 0)
    {
        Serial.print("OK ");
        print_status(app, hal_millis());
        return;
    }

    // ARM / DISARM
    if (strcmp(line, "ARM") == 0)
    {
        app->state = APP_ARMED;
        Serial.println("OK ARMED");
        return;
    }

    if (strcmp(line, "DISARM") == 0)
    {
        app->state = APP_IDLE;
        Serial.println("OK IDLE");
        return;
    }

    // FAULT
    if (strcmp(line, "FAULT") == 0)
    {
        app->fault_count++;
        app->state = APP_FAULT;
        Serial.println("OK FAULT");
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
            hal_led_set(true);
            Serial.println("OK LED ON");
            return;
        }

        if (strcmp(arg, "OFF") == 0)
        {
            app->led_override = true;        // manual mode enabled
            app->led_override_value = false; // manual value
            hal_led_set(false);
            Serial.println("OK LED OFF");
            return;
        }

        if (strcmp(arg, "AUTO") == 0)
        {
            app->led_override = false; // return control to heartbeat
            Serial.println("OK LED AUTO");
            return;
        }

        Serial.println("ERR LED expects ON OFF AUTO");
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
            Serial.println("ERR RATE expects an integer");
            return;
        }
        while (*end == ' ' || *end == '\t')
        {
            end++;
        }
        if (*end != '\0')
        {
            Serial.println("ERR RATE expects only an integer");
            return;
        }

        // Clamp to reasonable bounds for MVP
        if (ms < 10 || ms > 60000)
        {
            Serial.println("ERR RATE out of range (10..60000)");
            return;
        }

        app->telemetry_period_ms = (uint32_t)ms;
        Serial.println("OK RATE SET");
        return;
    }

    Serial.println("ERR Unknown command");
}
