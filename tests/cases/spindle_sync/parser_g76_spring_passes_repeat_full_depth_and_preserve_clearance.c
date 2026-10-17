#include "support/encoder_thread_motion_host.h"
int main(void)
{
    prepare_encoder_thread_motion();
    CHECK(sync_parser_block("G76Z-1P1I-1J0.5K1H2") == Status_OK);
    CHECK(protocol_buffer_synchronize());
    CHECK(sync_encoder_resets == 4);
    CHECK(physical_position[X_AXIS] == 800 && physical_position[Z_AXIS] == -80);
    CHECK(axis_pulses[X_AXIS] == 1200 && axis_pulses[Z_AXIS] == 560);
    CHECK(plan_get_current_block() == NULL && !sys.abort && sys.alarm == Alarm_None);
    return EXIT_SUCCESS;
}
