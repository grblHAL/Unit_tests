#include "support/paired_pwm_program_host.h"
int main(void)
{
    prepare_paired_pwm_program_mode(Mode_Laser);
    CHECK(!spindle_get(0)->cap.laser && spindle_get(1)->cap.laser);
    CHECK(spindle_program_block("M4S8000$1") == Status_OK);
    CHECK(spindle_program_block("G1X10F100") == Status_OK);
    plan_block_t *block = plan_get_current_block();
    CHECK(block && block->spindle.hal == spindle_get(1));
    CHECK(block->condition.is_rpm_rate_adjusted);
    NEAR(block->spindle.rpm, 8000);
    CHECK(!actual_spindle_states[0].on);
    return EXIT_SUCCESS;
}
