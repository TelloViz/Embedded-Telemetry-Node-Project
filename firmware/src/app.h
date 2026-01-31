// app.h
#pragma once
#include <stdint.h>
#include <stdbool.h>

typedef enum {
    APP_BOOT = 0,
    APP_IDLE,
    APP_ARMED,
    APP_FAULT
} app_state_t;

typedef struct {
    app_state_t state;
    bool led_forced_on;
    uint32_t telemetry_period_ms;
    uint32_t last_heartbeat_ms;
    uint32_t boot_ms;
    uint32_t fault_count;
} app_t;

void app_init(app_t* app, uint32_t now_ms);
void app_tick(app_t* app, uint32_t now_ms);
void app_handle_command(app_t* app, const char* line);