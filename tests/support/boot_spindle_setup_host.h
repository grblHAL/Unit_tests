#pragma once
#include "support/boot_host.h"
#include "spindle_control.h"
static spindle_ptrs_t setup_spindles[2];
static unsigned setup_spindle_configurations[2], setup_spindle_outputs[2];
static spindle_state_t setup_spindle_states[2];
static bool configure_setup_spindle(spindle_ptrs_t *spindle)
{
    CHECK(spindle->id >= 0 && spindle->id < 2);
    setup_spindle_configurations[spindle->id]++;
    return true;
}
static void output_setup_spindle(spindle_ptrs_t *spindle, spindle_state_t state, float rpm)
{
    CHECK(spindle->id >= 0 && spindle->id < 2);
    (void)rpm;
    setup_spindle_states[spindle->id] = state;
    setup_spindle_outputs[spindle->id]++;
}
static spindle_state_t state_setup_spindle(spindle_ptrs_t *spindle)
{
    CHECK(spindle->id >= 0 && spindle->id < 2);
    return setup_spindle_states[spindle->id];
}
static void register_setup_spindle(unsigned i)
{
    CHECK(i < 2);
    const char *names[] = {"primary", "secondary"};
    setup_spindles[i] = (spindle_ptrs_t){.type = SpindleType_Basic,
        .ref_id = (uint8_t)(10 * (i + 1)), .rpm_min = 1000, .rpm_max = 12000,
        .cap = {.direction = true, .rpm_range_locked = true},
        .config = configure_setup_spindle, .set_state = output_setup_spindle,
        .get_state = state_setup_spindle};
    CHECK(spindle_register(&setup_spindles[i], names[i]) == (spindle_id_t)i);
}
static void register_primary_during_init(void)
{
    register_setup_spindle(0);
}
static void register_setup_spindles(settings_t *current)
{
    CHECK(current == &settings);
    CHECK(boot_setup_calls == 1 && sys.ioinit_pending);
    CHECK(spindle_get_count() == 1);
    register_setup_spindle(1);
}
