#include "support/analog_motion_host.h"
#include "report.h"
#include "check.h"
static float analog_report_value(xbar_t *pin) { CHECK(pin->pin == 9); return 123; }

int main(void)
{
    prepare_analog_motion();
    xbar_t *pin = &analog_pins[Port_Input][0];
    pin->description = "sensor";
    pin->pin = 9;
    pin->cap.resolution = Resolution_12bit;
    pin->get_value = analog_report_value;
    CHECK(report_pin_states(STATE_IDLE, NULL) == Status_OK);
    CHECK(strstr(engine_output, "[PINSTATE:AIN|sensor|9|||123|12]" ASCII_EOL) != NULL);
    return EXIT_SUCCESS;
}
