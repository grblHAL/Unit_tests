#include "support/analog_motion_host.h"
#include "report.h"
#include "check.h"
static float dac_value(xbar_t *pin) { CHECK(pin->pin == 10); return 123; }
int main(void)
{
    prepare_analog_motion();
    xbar_t *pin = &analog_pins[Port_Output][0];
    pin->description = "dac";
    pin->pin = 10;
    pin->cap.resolution = Resolution_12bit;
    pin->get_value = dac_value;
    CHECK(report_pin_states(STATE_IDLE, NULL) == Status_OK);
    CHECK(strstr(engine_output, "[PINSTATE:AOUT|dac|10|N|N|123|12]" ASCII_EOL) != NULL);
    return EXIT_SUCCESS;
}
