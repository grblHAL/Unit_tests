#include "support/claimed_io_motion_host.h"
int main(void)
{
    prepare_analog_motion();
    uint8_t digital = 0, analog = 0;
    CHECK(ioport_claim(Port_Digital, Port_Output, &digital, "Plugin relay") != NULL);
    CHECK(ioport_claim(Port_Analog, Port_Output, &analog, "Plugin setpoint") != NULL);
    CHECK(io_block("M62P0") == Status_OK);
    CHECK(io_block("M67E0Q50") == Status_OK);
    queue_motion_program("G1X1F100");
    CHECK(output_calls == 0 && analog_output_calls == 0);
    execute_motion_program();
    CHECK(axis_pulses[X_AXIS] == 80 && physical_position[X_AXIS] == 80);
    CHECK(output_calls == 1 && physical_output == 1 && output_value);
    CHECK(analog_output_calls == 1 && analog_output_port == 1);
    NEAR(analog_output_value, 50);
    CHECK(ioport_digital_out(digital, 0));
    CHECK(ioport_analog_out(analog, 25));
    CHECK(output_calls == 2 && physical_output == 0 && !output_value);
    CHECK(analog_output_calls == 2 && analog_output_port == 0);
    NEAR(analog_output_value, 25);
    return EXIT_SUCCESS;
}
