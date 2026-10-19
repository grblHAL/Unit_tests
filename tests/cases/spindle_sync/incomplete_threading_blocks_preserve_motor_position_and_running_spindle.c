#include "support/encoder_thread_motion_host.h"
int main(void)
{
    prepare_encoder_thread_motion();
    const struct { const char *text; status_code_t error; } cases[] = {
        {"G76Z-1", Status_GcodeValueWordMissing},
        {"G76Z-1I-1", Status_GcodeValueOutOfRange},
        {"G76Z-1J0.5", Status_GcodeValueOutOfRange},
        {"G76Z-1K1", Status_GcodeValueOutOfRange},
        {"G76Z-1P1", Status_GcodeValueOutOfRange}
    };
    for(unsigned i = 0; i < sizeof(cases) / sizeof(cases[0]); i++) {
        CHECK(sync_parser_block(cases[i].text) == cases[i].error);
        CHECK(physical_position[X_AXIS] == 800 && physical_position[Z_AXIS] == 0);
        CHECK(axis_pulses[X_AXIS] == 0 && axis_pulses[Y_AXIS] == 0 && axis_pulses[Z_AXIS] == 0);
        CHECK(plan_get_current_block() == NULL && gc_state.modal.motion == MotionMode_Seek);
        CHECK(thread_encoder_state.on && sync_motion_feedback.rpm == 100);
    }
    CHECK(sync_parser_block("G1X11F100") == Status_OK);
    CHECK(protocol_buffer_synchronize());
    CHECK(physical_position[X_AXIS] == 880 && axis_pulses[X_AXIS] == 80);
    CHECK(physical_position[Z_AXIS] == 0 && axis_pulses[Z_AXIS] == 0);
    CHECK(sys.alarm == Alarm_None && !sys.abort);
    return EXIT_SUCCESS;
}
