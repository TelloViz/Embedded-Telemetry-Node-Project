// hal_led.h
#pragma once
#include <stdbool.h>

/*
    HAL LED Interface

    Responsibilities:
    - Abstract LED hardware operations.

    Invariants:
    - hal_led_init() must be called before other methods.
    - hal_led_set() and hal_led_toggle() must be non-blocking.
*/
namespace hal::led
{
  /*
    IHalLed Interface

    Responsibilities:
    - Define LED hardware abstraction methods.

    Invariants:
    - Implementations must provide concrete behavior for all methods.
  */
  class IHalLed {
    public:
    virtual ~IHalLed() = default;
    virtual void hal_led_init() = 0;
    virtual void hal_led_set(bool on) = 0;
    virtual void hal_led_toggle() = 0;
  };


  /*
    HalLedPico Implementation

    Responsibilities:
    - Provide concrete LED hardware operations for Raspberry Pi Pico.

    Invariants:
    - Must implement all IHalLed methods.
  */
  class HalLedPico : public IHalLed {
  public:
  void hal_led_init(void) override;   // Init LED hardware
  void hal_led_set(bool on) override; // Set LED state
  void hal_led_toggle(void) override; // Toggle LED state
  };
} // namespace hal::led