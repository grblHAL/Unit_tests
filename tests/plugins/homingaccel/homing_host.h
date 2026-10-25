#pragma once
#include "driver.h"
#include "check.h"
#include "grbl/nvs_buffer.h"
void homing_accel_init(void);
void ha_prepare(bool chain);
void ha_start(bool chain);
void ha_set(unsigned axis, float value);
float ha_get(unsigned axis);
void ha_rate(uint8_t mask);
void ha_complete(uint8_t mask, bool success);
extern setting_details_t *registered_settings;
extern unsigned calls[N_AXIS], rate_calls, complete_calls, settings_calls, options, saves;
extern float acceleration[N_AXIS];
extern bool alloc_ok, accept_override;
