// hal_led.cpp
#include <Arduino.h>
#include "hal_led.h"

// For Pico Arduino, LED_BUILTIN maps to the onboard LED pin.
// Keep the "hardware specifics" here, not in app log.
static bool s_led_on = false;

/*
    * Initialize the LED hardware.
*/
void hal_led_init(void) {
    pinMode(LED_BUILTIN, OUTPUT);
    s_led_on = false;
    digitalWrite(LED_BUILTIN, LOW); // Turn off LED initially
}

/* 
    * Set the LED state.
*/
void hal_led_set(bool on) {
    s_led_on = on;
    digitalWrite(LED_BUILTIN, on ? HIGH : LOW);
}

/* 
    * Toggle the LED state.
*/
void hal_led_toggle(void) {
    hal_led_set(!s_led_on);
}