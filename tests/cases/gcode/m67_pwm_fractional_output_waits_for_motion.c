#include "support/analog_motion_host.h"
#include "check.h"

int main(void)
{
    analog_pins[Port_Output][1].cap.pwm = true;
    analog_pins[Port_Output][1].mode.pwm = true;
    prepare_analog_motion();
    CHECK(io_block("M67E1Q1.25") == Status_OK);
    queue_motion_program("G1X1F100");
    CHECK(analog_output_calls == 0);
    execute_motion_program();
    CHECK(analog_output_calls == 1 && analog_output_port == 1);
    NEAR(analog_output_value, 1.25f);
    CHECK(physical_position[X_AXIS] == 80 && axis_pulses[X_AXIS] == 80);
    return EXIT_SUCCESS;
}
