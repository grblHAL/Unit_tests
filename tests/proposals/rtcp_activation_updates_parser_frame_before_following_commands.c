#include "support/boot_stream_motion_host.h"
#include "kinematics/interface.h"
static bool observed_activation;
static void observe_activation_frame(void)
{
    if(!observed_activation && boot_motion_ack_count() == 2) {
        coord_data_t reported;
        kinematics.transform_steps_to_cartesian(&reported, (mpos_t *)sys.position);
        observed_activation = true;
        fprintf(stderr, "After M851: parser XYZ=%f,%f,%f; current RTCP XYZ=%f,%f,%f\n",
            gc_state.position[0], gc_state.position[1], gc_state.position[2],
            reported.x, reported.y, reported.z);
        CHECK(fabsf(gc_state.position[0] - reported.x) < .001f);
        CHECK(fabsf(gc_state.position[1] - reported.y) < .001f);
        CHECK(fabsf(gc_state.position[2] - reported.z) < .001f);
        CHECK(protocol_enqueue_realtime_command(CMD_EXIT));
    }
}
int main(void)
{
    char program[64];
    snprintf(program, sizeof(program), "$%u=3\nM851\n", (unsigned)Settings_RotaryAxes);
    boot_motion_physical_nvs = true;
    prepare_boot_stream_motion(program);
    boot_before_read = observe_activation_frame;
    CHECK(grbl_enter() == 0);
    CHECK(observed_activation && boot_wake_calls == 0);
    return EXIT_SUCCESS;
}
