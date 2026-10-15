#include "support/paired_pwm_program_host.h"
int main(void)
{
    prepare_paired_pwm_program_mode(Mode_Laser);
    CHECK(spindle_program_block("M3S6000$0") == Status_OK);
    CHECK(spindle_program_block("M4S8000$1") == Status_OK);
    CHECK(spindle_program_block("M5$-1") == Status_OK);
    CHECK(!actual_spindle_states[0].on && !actual_spindle_states[1].on);
    CHECK(spindle_program_block("G1X10F100") == Status_OK);
    plan_block_t *block = plan_get_current_block();
    CHECK(block && !block->condition.is_rpm_rate_adjusted);
    CHECK(!block->spindle.state.on);
    return EXIT_SUCCESS;
}
