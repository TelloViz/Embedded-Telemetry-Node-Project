#include <unity.h>
#include <cstring>
#include "app.h"
#include "hal/led/hal_led.h"
#include "hal/time/hal_time.h"
#include "hal/serial/serial_io.h"


// Manual mocks for HAL interfaces
class MockHalLed : public hal::led::IHalLed {
    public:
    bool init_called = false;
    bool set_called = false;
    bool last_set_value = false;
    bool toggle_called = false;

    void hal_led_init() override { init_called = true; }
    void hal_led_set(bool on) override { set_called = true; last_set_value = on; }
    void hal_led_toggle() override { toggle_called = true; }
};

class MockHalTime : public hal::time::IHalTime {
    public:
    uint32_t millis_value = 1000;
    uint32_t hal_millis() override {return millis_value; }
};

class MockHalSerial : public hal::serial::ISerialIo {
    public:
    bool readline_called = false;
    char last_print[256] = {0};

    bool serial_readline(char *out, size_t out_cap) override {
        readline_called = true;
        // Simulate no input for simplicity
        return false;
    }

    void hal_serial_print(const char *str) override {
        strncpy(last_print, str, sizeof(last_print) - 1);
        last_print[sizeof(last_print) - 1] = '\0';
    }
};

void test_app_init() {
    MockHalLed mockLed;
    MockHalTime mockTime;
    MockHalSerial mockSerial;
    app::app_t app;

    mockTime.millis_value = 1000;
    app::app_init(&app, mockTime.millis_value, &mockLed, &mockTime, &mockSerial);

    TEST_ASSERT_EQUAL(app::app_state_t::APP_IDLE, app.state);
    TEST_ASSERT_TRUE(mockLed.init_called); // Assuming app_init calls hal_led_init
    TEST_ASSERT_EQUAL(1000, app.boot_ms);
}

void test_app_tick_led_override() {
    MockHalLed mockLed;
    MockHalTime mockTime;
    MockHalSerial mockSerial;
    app::app_t app;

    app::app_init(&app, 1000, &mockLed, &mockTime, &mockSerial);
    app.led_override = true;
    app.led_override_value = true;

    app::app_tick(&app, 1000);

    TEST_ASSERT_TRUE(mockLed.set_called);
    TEST_ASSERT_EQUAL(true, mockLed.last_set_value);
}

void test_app_tick_heartbeat() {
    MockHalLed mockLed;
    MockHalTime mockTime;
    MockHalSerial mockSerial;
    app::app_t app;

    app::app_init(&app, 1000, &mockLed, &mockTime, &mockSerial);
    app.led_override = false;
    app.last_heartbeat_ms = 4000; // 3 seconds

    app::app_tick(&app, 2001); // More than HEARTBEAT_PERIOD_MS later

    TEST_ASSERT_TRUE(mockLed.toggle_called);
}

void test_app_handle_command_led_off() {
    MockHalLed mockLed;
    MockHalTime mockTime;
    MockHalSerial mockSerial;
    app::app_t app;

    app::app_init(&app, 1000, &mockLed, &mockTime, &mockSerial);

    app::app_handle_command(&app, "LED OFF");

    TEST_ASSERT_TRUE(app.led_override);
    TEST_ASSERT_EQUAL(false, app.led_override_value);
    TEST_ASSERT_TRUE(mockLed.set_called);
    TEST_ASSERT_EQUAL(false, mockLed.last_set_value);
    TEST_ASSERT_EQUAL_STRING("OK LED OFF", mockSerial.last_print);
}


int main() {
    UNITY_BEGIN();
    RUN_TEST(test_app_init);
    RUN_TEST(test_app_tick_led_override);
    RUN_TEST(test_app_tick_heartbeat);
    RUN_TEST(test_app_handle_command_led_off);
    return UNITY_END();
}