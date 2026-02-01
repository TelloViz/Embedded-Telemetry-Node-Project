// hal_led.h
#pragma once
#include <stdbool.h>

/*
  HAL LED module

  Problem this solves:
  - Provide a small, board-agnostic API for controlling a status LED.
  - Hide hardware specifics (GPIO pin, active-low wiring, framework calls) from app logic.

  Inputs and outputs:
  - Inputs: calls to hal_led_init(), hal_led_set(on), hal_led_toggle().
  - Output: side effect on the physical LED.
  - Contract: 'true' means the LED is visibly on to a user, regardless of underlying GPIO polarity.

  Invariants:
  - hal_led_init() must be called before any other hal_led_* function.
  - All functions must be non-blocking and fast (safe to call every loop tick).
  - hal_led_set(true/false) and hal_led_toggle() must remain consistent with the "visible LED" contract.
*/
namespace hal::led
{
  class IHalLed {
    public:
    virtual ~IHalLed() = default;
    virtual void hal_led_init() = 0;
    virtual void hal_led_set(bool on) = 0;
    virtual void hal_led_toggle() = 0;
  };

  class HalLed : public IHalLed {
  public:
  void hal_led_init(void) override;   // Init LED hardware
  void hal_led_set(bool on) override; // Set LED state
  void hal_led_toggle(void) override; // Toggle LED state
  };
} // namespace hal::led