#include "support/motion_program_host.h"
#include "ngc_params.h"
int main(void)
{
    prepare_motion_program();
    queue_motion_program("G1X1F100");
    plan_block_t *first = plan_get_current_block();
    unsigned available = plan_get_block_buffer_available();
    const char *labels[] = {"O1.5SUB", "O10.01CALL", "O2.9999SUB"};
    for(unsigned i = 0; i < sizeof(labels) / sizeof(*labels); i++) {
        char command[32]; strcpy(command, labels[i]);
        CHECK(gc_execute_block(command) == Status_GcodeCommandValueNotInteger);
        CHECK(ngc_call_level() == 0 && !gc_state.skip_blocks);
        CHECK(plan_get_current_block() == first && plan_get_block_buffer_available() == available);
        CHECK(gc_state.modal.motion == MotionMode_Linear);
        NEAR(gc_state.position[X_AXIS], 1);
        NEAR(gc_state.feed_rate, 100);
        CHECK(physical_position[X_AXIS] == 0 && axis_pulses[X_AXIS] == 0);
    }
    queue_motion_program("G1X2F100");
    execute_motion_program();
    CHECK(physical_position[X_AXIS] == 160 && sys.position[X_AXIS] == 160);
    CHECK(axis_pulses[X_AXIS] == 160 && axis_pulses[Y_AXIS] == 0 && axis_pulses[Z_AXIS] == 0);
    CHECK(ngc_call_level() == 0 && !sys.abort && sys.alarm == Alarm_None);
    return EXIT_SUCCESS;
}
