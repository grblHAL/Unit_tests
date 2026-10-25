#include "support/queued_motion_rejection_host.h"
#include "ngc_params.h"

int main(void)
{
    prepare_motion_program();
    CHECK(grbl.on_macro_execute != NULL);
    CHECK(ngc_param_set(24, 99));
    queue_motion_program("G1X1F100");
    check_rejected_block_preserves_queued_motion("G65P100X12", Status_GcodeValueOutOfRange);
    CHECK(ngc_call_level() == 0 && gc_state.g66_args == NULL);
    float value;
    CHECK(ngc_param_get(24, &value)); NEAR(value, 99);
    char retry[] = "G65P3I100Q9";
    CHECK(gc_execute_block(retry) == Status_OK);
    CHECK(ngc_param_get(100, &value)); NEAR(value, 9);
    CHECK(ngc_param_get(24, &value)); NEAR(value, 99);
    CHECK(ngc_call_level() == 0 && plan_get_current_block() == NULL);
    CHECK(axis_pulses[X_AXIS] == 80 && physical_position[X_AXIS] == 80);
    return EXIT_SUCCESS;
}
