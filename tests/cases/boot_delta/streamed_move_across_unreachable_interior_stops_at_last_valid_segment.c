#include "support/boot_delta_stream_motion_host.h"
#include "kinematics/interface.h"
static bool approach_seen, stopped_seen;
static coord_data_t stopped_cartesian;
static unsigned command_responses(void)
{
    unsigned count = boot_motion_ack_count();
    const char *cursor = engine_output;
    while((cursor = strstr(cursor, "error:"))) {
        CHECK(cursor == engine_output || cursor[-1] == '\n');
        if(strchr(cursor, '\n')) count++;
        cursor += strlen("error:");
    }
    return count;
}
static void observe_delta_interior_stop(sys_state_t state)
{
    boot_motion_foreground(state);
    if((state == STATE_IDLE || state == STATE_ALARM) && plan_get_current_block() == NULL) {
        mpos_t steps;
        coord_data_t cartesian;
        memcpy(&steps, sys.position, sizeof(steps));
        kinematics.transform_steps_to_cartesian(&cartesian, &steps);
        if(boot_motion_ack_count() == 2 && !approach_seen) {
            CHECK(isfinite(cartesian.x) && isfinite(cartesian.y) && isfinite(cartesian.z));
            CHECK(fabsf(cartesian.x + 250) < 1 && fabsf(cartesian.y) < 1);
            CHECK(fabsf(cartesian.z + 150) < 1);
            coord_data_t other_endpoint = {.x = 250, .y = 0, .z = -150}, motors, roundtrip;
            kinematics.transform_from_cartesian(&motors, &other_endpoint);
            mpos_t endpoint_steps;
            for(unsigned axis = 0; axis < N_AXIS; axis++) {
                CHECK(isfinite(motors.values[axis]));
                endpoint_steps.values[axis] = lroundf(motors.values[axis] * settings.axis[axis].steps_per_mm);
            }
            kinematics.transform_steps_to_cartesian(&roundtrip, &endpoint_steps);
            CHECK(isfinite(roundtrip.x) && fabsf(roundtrip.x - 250) < 1);
            CHECK(fabsf(roundtrip.y) < 1 && fabsf(roundtrip.z + 150) < 1);
            approach_seen = true;
        }
        if(command_responses() >= 4 && !stopped_seen) {
            CHECK(approach_seen);
            stopped_cartesian = cartesian;
            stopped_seen = true;
        }
        if(!boot_motion_exit_queued && stopped_seen && boot_reads == strlen(boot_program) &&
           command_responses() == boot_motion_expected_acks && strstr(engine_output, "[GC:")) {
            boot_motion_exit_queued = true;
            CHECK(protocol_enqueue_realtime_command(CMD_EXIT));
        }
    }
}
static void install_delta_interior_stop_driver(void)
{
    install_delta_motion_driver();
    grbl.on_execute_delay = observe_delta_interior_stop;
}
int main(void)
{
    /* Both endpoints have real inverse solutions; their straight connecting
       line crosses the central region unreachable by the configured rods. */
    prepare_boot_delta_stream_motion("G53G0X-250Y0Z-150\nG4P0\nG53G0X250Y0Z-150\nG4P0\n$G\n");
    boot_during_init = install_delta_interior_stop_driver;
    boot_on_realtime = observe_delta_interior_stop;
    CHECK(grbl_enter() == 0);
    CHECK(approach_seen && stopped_seen && plan_get_current_block() == NULL);
    CHECK(isfinite(stopped_cartesian.x) && isfinite(stopped_cartesian.y) && isfinite(stopped_cartesian.z));
    fprintf(stderr, "Delta interior stop: X=%g Y=%g Z=%g\n",
        (double)stopped_cartesian.x, (double)stopped_cartesian.y, (double)stopped_cartesian.z);
    CHECK(stopped_cartesian.x < -100 && stopped_cartesian.x > -250);
    CHECK(fabsf(stopped_cartesian.y) < 1 && fabsf(stopped_cartesian.z + 150) < 1);
    CHECK(command_responses() == 5);
    CHECK(boot_motion_exit_queued && sys.flags.exit && sys.abort);
    for(unsigned axis = 0; axis < N_AXIS; axis++) CHECK(sys.position[axis] == boot_motor_position[axis]);
    CHECK(strstr(engine_output, "[GC:") != NULL);
    return EXIT_SUCCESS;
}
