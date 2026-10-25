#include "support/motion_program_host.h"
int main(void)
{
    prepare_motion_program();
    settings.mode = Mode_Lathe;
    queue_motion_program("G1X1F100");
    plan_block_t *first = plan_get_current_block();
    unsigned available = plan_get_block_buffer_available();
    const char *modes[] = {"G71", "G71.1", "G71.2", "G72", "G72.1", "G72.2"};
    for(unsigned i = 0; i < sizeof(modes) / sizeof(*modes); i++) {
        char command[64], xy[] = "G17", zx[] = "G18";
        CHECK(gc_execute_block(xy) == Status_OK);
        snprintf(command, sizeof(command), "G17%sX2Z-1Q7F100", modes[i]);
        CHECK(gc_execute_block(command) == Status_GcodeIllegalPlane);
        CHECK(gc_execute_block(zx) == Status_OK);
        snprintf(command, sizeof(command), "%sX2Z-1F100", modes[i]);
        status_code_t status = gc_execute_block(command);
        CHECK(status == Status_GcodeValueWordMissing);
        CHECK(plan_get_current_block() == first && plan_get_block_buffer_available() == available);
        CHECK(gc_state.modal.motion == MotionMode_Linear && gc_state.modal.plane_select == PlaneSelect_ZX);
        NEAR(gc_state.position[X_AXIS], 1);
        NEAR(gc_state.position[Z_AXIS], 0);
        NEAR(gc_state.feed_rate, 100);
    }
    queue_motion_program("G18G1Z1F100");
    execute_motion_program();
    CHECK(axis_pulses[X_AXIS] == 80 && physical_position[X_AXIS] == 80);
    CHECK(axis_pulses[Z_AXIS] == 80 && physical_position[Z_AXIS] == 80);
    CHECK(axis_pulses[Y_AXIS] == 0);
    return EXIT_SUCCESS;
}
