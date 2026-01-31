// hal_led.h
#pragma once
#include <stdbool.h>

/*
hal_led.h provides an interface for initializing and controlling an
LED on the hardware abstraction layer (HAL). It includes functions to
intitialize the LED hardware, set the LED state (on/off), and toggle the LED. 
*/

void hal_led_init(void); // Init LED hardware
void hal_led_set(bool on); // Set LED state
void hal_led_toggle(void); // Toggle LED state

bool hal_led_get_state(void); // Get current LED state

