// main.cpp
#include <Arduino.h>
#include "app.h"
#include "hal/led/hal_led.h"
#include "hal/time/hal_time.h"
#include "hal/serial/serial_io.h"

/*
    Main application entry point for the embedded telemetry node.

    Responsibilities:
    - Initialize hardware and application state.
    - Handle serial commands.
    - Run periodic application logic.

    Invariants:
    - setup() is called once at boot.
    - loop() is called repeatedly thereafter.
    - All operations must be non-blocking to maintain responsiveness.
*/

static app::app_t g_app; // Global app state

/*
    Arduino setup function
    - Initializes serial communication, LED hardware, and app state.
    - Prints "BOOT OK" to indicate successful startup.
*/
void setup()
{
    Serial.begin(115200);                   // Initialize serial communication

    static hal::led::HalLed hLed;
    static hal::time::HalTime hTime;
    static hal::serial::HalSerial hSerial;

    hLed.hal_led_init();               // Initialize LED hardware
    uint32_t now = hTime.hal_millis(); // Get current time
    app::app_init(&g_app, now, &hLed, &hTime, &hSerial);             // Init app state
    Serial.println("BOOT OK");
}

/*
        Arduino loop function
        - Reads serial commands and passes them to the app handler.
    - Calls app_tick() to run periodic tasks.
*/
void loop()
{
    uint32_t now = g_app.time->hal_millis(); // Current time

    // Read one line if available (non-blocking).
    char line[96]; // Buff for incoming command
    if (g_app.serial->serial_readline(line, sizeof(line)))
    {
        app::app_handle_command(&g_app, line); // handle command
    }

    // Run periodic tasks.
    app::app_tick(&g_app, now);
}
