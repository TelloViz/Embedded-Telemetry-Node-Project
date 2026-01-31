// main.cpp
#include <Arduino.h>
#include "app.h"
#include "hal/led/hal_led.h"
#include "hal/time/hal_time.h"
#include "serial_io.h"

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


static app_t g_app; // Global app state

/*
    Arduino setup function
    - Initializes serial communication, LED hardware, and app state.
    - Prints "BOOT OK" to indicate successful startup.
*/
void setup() {
    Serial.begin(115200); // Initialize serial communication
    hal::led::hal_led_init(); // Initialize LED hardware
    uint32_t now = hal::time::hal_millis(); // Get current time
    app_init(&g_app, now); // Init app state
    Serial.println("BOOT OK");
}

/*
    Arduino loop function
    - Reads serial commands and passes them to the app handler.
    - Calls app_tick() to run periodic tasks.
*/
void loop() {
    uint32_t now = hal::time::hal_millis(); // Current time

    // Read one line if available (non-blocking).
    char line[96]; // Buff for incoming command
    if(serial_readline(line, sizeof(line))) {
        app_handle_command(&g_app, line); // handle command
    }

    // Run periodic tasks.
    app_tick(&g_app, now);
}

