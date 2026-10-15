#pragma once
#include "support/boot_legacy_host.h"

static bool legacy_limits_enabled, legacy_limits_saw_enable;
static unsigned legacy_limits_enable_calls;
static void configure_legacy_limit_interrupts(bool enabled, axes_signals_t homing)
{
    (void)homing;
    legacy_limits_enabled = enabled;
    legacy_limits_saw_enable |= enabled;
    legacy_limits_enable_calls++;
}
static void install_legacy_limit_board(settings_t *current)
{
    CHECK(current == &settings);
    hal.limits_cap.min.mask = AXES_BITMASK;
    hal.limits.enable = configure_legacy_limit_interrupts;
}
static void persist_legacy_homing_configuration(void)
{
    settings.homing.cycle[0].mask = Z_AXIS_BIT;
    settings.homing.cycle[1].mask = X_AXIS_BIT | Y_AXIS_BIT;
    settings.homing.locate_cycles = 1;
    settings.homing.pulloff = 1;
    for(unsigned axis = 0; axis < N_AXIS; axis++) {
        settings.axis[axis].homing_feed_rate = 50;
        settings.axis[axis].homing_seek_rate = 500;
    }
    settings_write_global();
}
static inline void run_legacy_limit_board(const char *program)
{
    boot_program = program;
    boot_during_init = persist_legacy_homing_configuration;
    boot_during_setup = install_legacy_limit_board;
    run_legacy_boot_program();
    CHECK(strstr(engine_output, "error:") == NULL);
}
