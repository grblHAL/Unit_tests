#pragma once
#include "driver.h"
#include "check.h"
#include "task.h"
#include "stepper2.h"
extern grbl_t grbl;
extern settings_t settings;
extern system_t sys;
extern setting_details_t *stepper_settings;
extern bool stepper_driver_ok, stepper_clock_ok;
extern unsigned stepper_pulses, stepper_forward, stepper_reverse, stepper_claims, stepper_warnings,
    stepper_saves, stepper_realtime, stepper_delays, stepper_previous_settings;
extern uint8_t stepper_enabled;
extern bool stepper_claimed;
extern driver_settings_save_ptr stepper_save;
void stepper_prepare(void);
void stepper_poll(unsigned count);
void stepper_cruise(spindle_ptrs_t *s);
void stepper_stop(spindle_ptrs_t *s);
void stepper_spindle_init(void);
