#include "support/multi_spindle_host.h"

int main(void)
{
    spindle_configuration_unavailable[1] = true;
    prepare_multi_spindle_program();
    CHECK(spindle_program_block("M3S3000") == Status_OK);
    unsigned primary_outputs = spindle_output_calls[0];
    CHECK(spindle_enable(1) == -1);
    CHECK(spindle_config_calls[1] == 1 && !spindle_is_enabled(1));
    CHECK(spindle_get(1) == NULL && spindle_get_default() == 0);
    CHECK(spindle_output_calls[1] == 0 && spindle_output_calls[0] == primary_outputs);
    CHECK(actual_spindle_states[0].on); NEAR(actual_spindle_rpm[0], 3000);
    spindle_configuration_unavailable[1] = false;
    CHECK(spindle_enable(1) == 1);
    CHECK(spindle_config_calls[1] == 2 && spindle_get(1)->id == 1);
    CHECK(spindle_output_calls[0] == primary_outputs);
    CHECK(spindle_program_block("M4S4200$1") == Status_OK);
    CHECK(actual_spindle_states[1].on && actual_spindle_states[1].ccw);
    NEAR(actual_spindle_rpm[1], 4200);
    CHECK(actual_spindle_states[0].on && !actual_spindle_states[0].ccw);
    NEAR(actual_spindle_rpm[0], 3000);
    CHECK(spindle_program_block("M5$1") == Status_OK);
    CHECK(!actual_spindle_states[1].on && actual_spindle_states[0].on);
    CHECK(spindle_output_calls[0] == primary_outputs);
    return EXIT_SUCCESS;
}
