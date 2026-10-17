#include "support/encoder_thread_motion_host.h"
#include "support/segmented_stop_stream_host.h"
int main(void)
{
    prepare_encoder_thread_motion();
    program_stop_in_drill = true;
    program_step_service = service_sync_parser_driver;
    configure_stopped_program_stream("G76Z-1P1I-1J0.5K1H2\nG1Z-5\n");
    finish_stopped_program();
    CHECK(sync_encoder_resets == 1); /* No subsequent cut or spring pass starts. */
    CHECK(program_stop_position[Z_AXIS] < 0 && program_stop_position[Z_AXIS] > -80);
    CHECK(!thread_encoder_state.on && sync_motion_feedback.rpm == 0);
    CHECK(sys.alarm == Alarm_None);
    return EXIT_SUCCESS;
}
