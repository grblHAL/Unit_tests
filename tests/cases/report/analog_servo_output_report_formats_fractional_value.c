#include "support/analog_motion_host.h"
#include "report.h"
#include "check.h"
static float servo_value(xbar_t *pin) { CHECK(pin->pin == 10); return 45.25f; }
int main(void)
{
    prepare_analog_motion();
    xbar_t *pin = &analog_pins[Port_Output][0];
    pin->description = "servo";
    pin->pin = 10;
    pin->mode.servo_pwm = pin->cap.servo_pwm = true;
    pin->get_value = servo_value;
    CHECK(report_pin_states(STATE_IDLE, NULL) == Status_OK);
    CHECK(strstr(engine_output, "[PINSTATE:AOUT|servo|10|S|S|45.25]" ASCII_EOL) != NULL);
    return EXIT_SUCCESS;
}
