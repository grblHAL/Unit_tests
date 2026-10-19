#pragma once
#include "support/macro_parser_host.h"
#include "support/canned_motion_host.h"
static inline void run_modal_macro_after_arc(const char *arc, int32_t x, int32_t y, int32_t z)
{
    prepare_canned_motion();
    grbl.on_macro_execute = capture_macro;
    CHECK(macro_block("G66P100X12Y8Z4") == Status_OK);
    CHECK(macro_calls == 0 && plan_get_current_block() == NULL);
    CHECK(macro_block(arc) == Status_OK);
    CHECK(protocol_buffer_synchronize());
    if(macro_calls != 1 || called_macro != 100 || macro_repeats != 1)
        fprintf(stderr, "G66 arc: calls=%u id=%lu repeats=%lu storedP=%g storedL=%g\n", macro_calls,
            (unsigned long)called_macro, (unsigned long)macro_repeats,
            (double)gc_state.g66_args->values.p, (double)gc_state.g66_args->values.l);
    CHECK(macro_calls == 1 && called_macro == 100 && macro_repeats == 1);
    NEAR(macro_x, 12); NEAR(macro_y, 8); NEAR(macro_z, 4);
    CHECK(ngc_call_level() == 0);
    CHECK(physical_position[X_AXIS] == x && physical_position[Y_AXIS] == y && physical_position[Z_AXIS] == z);
    CHECK(sys.position[X_AXIS] == x && sys.position[Y_AXIS] == y && sys.position[Z_AXIS] == z);
    CHECK(axis_pulses[X_AXIS] > 0 && axis_pulses[Y_AXIS] > 0);
    CHECK(macro_block("G67") == Status_OK && gc_state.g66_args == NULL);
    CHECK(macro_block("G91G1X1F100") == Status_OK);
    CHECK(protocol_buffer_synchronize());
    CHECK(macro_calls == 1);
    CHECK(physical_position[X_AXIS] == x + 80 && physical_position[Y_AXIS] == y && physical_position[Z_AXIS] == z);
    CHECK(sys.alarm == Alarm_None && !sys.abort && plan_get_current_block() == NULL);
}
