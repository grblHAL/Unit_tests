#include "support/analog_motion_host.h"
#include "support/queued_motion_rejection_host.h"
#include "check.h"

int main(void)
{
    analog_pins[Port_Output][1].cap.servo_pwm = true;
    analog_pins[Port_Output][1].mode.servo_pwm = true;
    prepare_analog_motion();
    queue_motion_program("G1X1F100");
    check_rejected_block_preserves_queued_motion("M68E1Q-0.25", Status_GcodeValueOutOfRange);
    CHECK(analog_output_calls == 0);
    CHECK(io_block("M68E1Q0") == Status_OK);
    CHECK(analog_output_calls == 1 && analog_output_port == 1);
    NEAR(analog_output_value, 0);
    return EXIT_SUCCESS;
}
