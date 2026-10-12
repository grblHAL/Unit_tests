#include "support/analog_motion_host.h"
#include "report.h"
#include "check.h"
static float pwm_report_value(xbar_t *pin) { CHECK(pin->pin == 10); return 12.5f; }

int main(void)
{
    prepare_analog_motion();
    xbar_t *pin = &analog_pins[Port_Output][0];
    pin->description = "laser";
    pin->pin = 10;
    pin->mode.pwm = pin->cap.pwm = true;
    pin->get_value = pwm_report_value;
    CHECK(report_pin_states(STATE_IDLE, NULL) == Status_OK);
    CHECK(strstr(engine_output, "[PINSTATE:AOUT|laser|10|P|P|12.50]" ASCII_EOL) != NULL);
    return EXIT_SUCCESS;
}
