#include "support/report_host.h"
#include "support/ioports_host.h"
#include "check.h"
static float relay_value(xbar_t *pin) { CHECK(pin->pin == 8); return 1; }
int main(void)
{
    prepare_report();
    register_ioports();
    xbar_t *pin = &digital_pins[Port_Output][0];
    pin->description = "relay";
    pin->pin = 8;
    pin->mode.inverted = true;
    pin->cap.invert = true;
    pin->get_value = relay_value;
    CHECK(report_pin_states(STATE_IDLE, NULL) == Status_OK);
    CHECK(strstr(engine_output, "[PINSTATE:DOUT|relay|8|I|I|1]" ASCII_EOL) != NULL);
    return EXIT_SUCCESS;
}
