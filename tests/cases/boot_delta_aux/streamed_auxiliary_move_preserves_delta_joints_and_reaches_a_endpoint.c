#include "support/boot_delta_stream_motion_host.h"
#include "check.h"

static void finish_auxiliary_program(sys_state_t state)
{
    boot_motion_foreground(state);
    if(!boot_motion_exit_queued && sys.driver_started && boot_reads >= strlen(boot_program) &&
       boot_motion_ack_count() == boot_motion_expected_acks && state_get() == STATE_IDLE &&
       plan_get_current_block() == NULL) {
        CHECK(protocol_enqueue_realtime_command(CMD_EXIT));
        boot_motion_exit_queued = true;
    }
}
int main(void)
{
    prepare_boot_delta_stream_motion("G91G1A1F100\n");
    boot_on_realtime = finish_auxiliary_program;
    CHECK(grbl_enter() == 0);
    CHECK(boot_motion_exit_queued && boot_motion_ack_count() == 1);
    CHECK(boot_setup_calls == 1 && boot_release_calls == 1);
    CHECK(plan_get_current_block() == NULL && strstr(engine_output, "error:") == NULL);
    fprintf(stderr, "Auxiliary requested=1, parser=%g, motor=%ld, pulses=%u\n",
        (double)gc_state.position[A_AXIS], (long)boot_motor_position[A_AXIS], boot_motor_pulses[A_AXIS]);
    CHECK(boot_motor_position[A_AXIS] == 80 && sys.position[A_AXIS] == 80);
    CHECK(boot_motor_pulses[A_AXIS] == 80);
    NEAR(gc_state.position[A_AXIS], 1);
    for(unsigned motor = 0; motor < 3; motor++) {
        CHECK(boot_motor_position[motor] == 0 && boot_motor_pulses[motor] == 0);
    }
    CHECK(fabsf(gc_state.position[Z_AXIS] - delta_zero_angle_height()) < .03f);
    return EXIT_SUCCESS;
}
