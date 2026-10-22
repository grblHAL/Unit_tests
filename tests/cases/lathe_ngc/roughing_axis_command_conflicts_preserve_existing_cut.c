#include "support/motion_program_host.h"
int main(void)
{
    prepare_motion_program();
    settings.mode = Mode_Lathe;
    queue_motion_program("G1X1F100");
    plan_block_t *first = plan_get_current_block();
    unsigned available = plan_get_block_buffer_available();
    const char *commands[] = {"G1G70X2Q7", "G1G71X2Q7", "G1G72X2Q7"};
    for(unsigned i = 0; i < sizeof(commands) / sizeof(*commands); i++) {
        char command[32]; strcpy(command, commands[i]);
        CHECK(gc_execute_block(command) == Status_GcodeAxisCommandConflict);
        CHECK(plan_get_current_block() == first && plan_get_block_buffer_available() == available);
        CHECK(gc_state.modal.motion == MotionMode_Linear);
        NEAR(gc_state.position[X_AXIS], 1); NEAR(gc_state.feed_rate, 100);
    }
    execute_motion_program();
    CHECK(axis_pulses[X_AXIS] == 80 && physical_position[X_AXIS] == 80);
    CHECK(axis_pulses[Y_AXIS] == 0 && axis_pulses[Z_AXIS] == 0);
    return EXIT_SUCCESS;
}
