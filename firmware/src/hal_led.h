// hal_led.h
#pragma once
#include <stdbool.h>

void hal_led_init(void); // Init LED hardware
void hal_led_set(bool on); // Set LED state
void hal_led_toggle(void); // Toggle LED state

bool hal_led_get_state(void); // Get current LED state