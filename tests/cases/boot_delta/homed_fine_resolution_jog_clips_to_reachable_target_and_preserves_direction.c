#include "support/boot_delta_homing_host.h"
static bool clipped_jog_finished;
static unsigned jog_services, sender_wait_polls;
static coord_data_t clipped_position;
static void service_homed_jog(sys_state_t state)
{
    CHECK(++jog_services < 300000);
    engine_ticks++;
    if(boot_homing_timer_running && (state == STATE_HOMING || state == STATE_CYCLE || state == STATE_JOG))
        stepper_driver_interrupt_handler();
    if(boot_delta_home_events == 1 && boot_reads == strlen(boot_program) &&
       (state == STATE_IDLE || state == STATE_ALARM) && plan_get_current_block() == NULL) {
        mpos_t steps;
        memcpy(steps.values, sys.position, sizeof(steps.values));
        kinematics.transform_steps_to_cartesian(&clipped_position, &steps);
        CHECK(sys.alarm == Alarm_None && !sys.abort);
        clipped_jog_finished = true;
        CHECK(protocol_enqueue_realtime_command(CMD_EXIT));
        boot_on_realtime = NULL;
    }
}
static int32_t read_after_positioning_finishes(void)
{
    const char *jog = strstr(boot_program, "$J=");
    CHECK(jog != NULL);
    if(boot_reads == (unsigned)(jog - boot_program) &&
       (state_get() != STATE_IDLE || plan_get_current_block() != NULL)) {
        sender_wait_polls++;
        return SERIAL_NO_DATA;
    }
    return read_char();
}
static void install_homed_jog_driver(void)
{
    install_delta_homing_driver();
    hal.stream.read = read_after_positioning_finishes;
    grbl.on_execute_delay = service_homed_jog;
}
int main(void)
{
    prepare_boot_delta_homing(false);
    boot_during_init = install_homed_jog_driver;
    boot_on_realtime = service_homed_jog;
    boot_program = "$100=2000\n$101=2000\n$102=2000\n$20=1\n$40=1\n$H\nG0Z-300\n$J=G91X1000F100\n$G\n";
    CHECK(grbl_enter() == 0);
    if(!clipped_jog_finished || boot_motion_ack_count() != 9)
        fprintf(stderr, "Delta jog: home=%u homed=%u state=%u ack=%u pos=%g,%g,%g output=%s\n",
        boot_delta_home_events, (unsigned)sys.homed.mask, (unsigned)state_get(), boot_motion_ack_count(),
        clipped_position.x, clipped_position.y, clipped_position.z, engine_output);
    CHECK(clipped_jog_finished && boot_delta_home_events == 1);
    CHECK(boot_motion_ack_count() == 9 && sender_wait_polls > 0);
    CHECK(sys.homed.mask == AXES_BITMASK);
    for(unsigned axis = 0; axis < 3; axis++) {
        NEAR(settings.axis[axis].steps_per_mm, 2000);
        CHECK(boot_motor_pulses[axis] > boot_delta_homing_pulses[axis]);
        CHECK(fabsf(gc_state.position[axis] - clipped_position.values[axis]) < .15f);
    }
    CHECK(isfinite(clipped_position.x) && clipped_position.x > 0 && clipped_position.x < 1000);
    CHECK(fabsf(clipped_position.y) < .15f && fabsf(clipped_position.z + 300) < .15f);
    CHECK(grbl.check_travel_limits(clipped_position.values, sys.homed, true, &sys.work_envelope));
    CHECK(plan_get_current_block() == NULL);
    CHECK(strstr(engine_output, "error:") == NULL);
    CHECK(boot_setup_calls == 1 && boot_release_calls == 1);
    return EXIT_SUCCESS;
}
