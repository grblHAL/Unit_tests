#include "support/spindle_sync_parser_host.h"
int main(void)
{
    prepare_sync_parser();
    gc_override_flags_t original = sys.override.control;
    CHECK(sync_parser_block("G33Z1K1") == Status_OK);
    CHECK(wake_calls == 1 && axis_pulses[Z_AXIS] == 80);
    CHECK(physical_position[Z_AXIS] == 80 && sys.position[Z_AXIS] == 80);
    CHECK(axis_pulses[X_AXIS] == 0 && axis_pulses[Y_AXIS] == 0);
    CHECK(sync_encoder_resets == 1 && sync_rpm_reads > 0 && sync_angle_reads > 0);
    CHECK(sys.override.control.value == original.value);
    CHECK(plan_get_current_block() == NULL && !sys.abort && sys.alarm == Alarm_None);
    return EXIT_SUCCESS;
}
