#include "support/motion_program_host.h"
#include "ngc_params.h"
int main(void)
{
    prepare_motion_program();
    queue_motion_program("G1X1F100");
    plan_block_t *first = plan_get_current_block();
    unsigned available = plan_get_block_buffer_available();
    const char *commands[] = {"O[1/0]CALL", "123"};
    const status_code_t expected[] = {Status_ExpressionDivideByZero, Status_ExpectedCommandLetter};
    for(unsigned i = 0; i < sizeof(commands) / sizeof(*commands); i++) {
        char block[32]; strcpy(block, commands[i]);
        CHECK(gc_execute_block(block) == expected[i]);
        CHECK(ngc_call_level() == 0);
        CHECK(plan_get_current_block() == first && plan_get_block_buffer_available() == available);
        CHECK(!gc_state.modal.units_imperial && !gc_state.modal.distance_incremental);
        NEAR(gc_state.position[X_AXIS], 1);
        NEAR(gc_state.feed_rate, 100);
    }
    queue_motion_program("G1X2F100");
    execute_motion_program();
    CHECK(axis_pulses[X_AXIS] == 160 && physical_position[X_AXIS] == 160);
    CHECK(sys.position[X_AXIS] == 160);
    return EXIT_SUCCESS;
}
