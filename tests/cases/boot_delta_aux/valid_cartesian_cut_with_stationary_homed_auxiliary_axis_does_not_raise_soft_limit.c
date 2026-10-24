#include "support/boot_delta_manual_first_host.h"
static bool false_soft_limit, exited_false_limit, first_cut_completed;
static void service_valid_auxiliary_cut(sys_state_t state)
{
    service_manual_a(state);
    if(!first_cut_completed && state == STATE_IDLE && !plan_get_current_block() && boot_motion_ack_count() == 6) {
        for(unsigned axis = 0; axis < 3; axis++) CHECK(boot_motor_pulses[axis] > pulses_after_xyz_home[axis]);
        CHECK(sys.position[A_AXIS] == 0 && boot_motor_pulses[A_AXIS] == 0);
        first_cut_completed = true;
    }
    if(sys.alarm == Alarm_SoftLimit) {
        false_soft_limit = true;
        if(!exited_false_limit) {
            exited_false_limit = true;
            CHECK(protocol_enqueue_realtime_command(CMD_EXIT));
        }
    }
}
static void install_valid_auxiliary_cut(void)
{
    install_manual_a_first();
    grbl.on_execute_delay = service_valid_auxiliary_cut;
}
int main(void)
{
    prepare_delta_manual_first("G91G1Z-1F100\nG4P0\n$20=1\nG1Z-1\n$G\n", 9);
    boot_during_init = install_valid_auxiliary_cut;
    boot_on_realtime = service_valid_auxiliary_cut;
    CHECK(grbl_enter() == 0);
    CHECK(manual_a_homing_events == 2 && sys.homed.mask == AXES_BITMASK);
    CHECK(sys.soft_limits.mask & A_AXIS_BIT);
    fprintf(stderr, "Valid delta cut: soft_limit=%u acks=%u A=%ld XYZpulse0=%u/%u\n",
        false_soft_limit, boot_motion_ack_count(), (long)sys.position[A_AXIS],
        boot_motor_pulses[0], pulses_after_xyz_home[0]);
    CHECK(first_cut_completed);
    CHECK(!false_soft_limit);
    CHECK(manual_a_finished && boot_motion_ack_count() == 9);
    CHECK(sys.position[A_AXIS] == 0 && boot_motor_pulses[A_AXIS] == 0);
    for(unsigned axis = 0; axis < 3; axis++) CHECK(boot_motor_pulses[axis] > pulses_after_xyz_home[axis]);
    CHECK(fabsf(gc_state.position[Z_AXIS] - (delta_zero_angle_height() - 2)) < .03f);
    CHECK(plan_get_current_block() == NULL);
    return EXIT_SUCCESS;
}
