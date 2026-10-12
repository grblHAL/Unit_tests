#include "support/report_host.h"
#include "support/ioports_host.h"
#include "check.h"

int main(void)
{
    prepare_report();
    register_ioports();
    xbar_t *pin = &digital_pins[Port_Output][0];
    pin->description = "relay";
    pin->pin = 8;
    CHECK(report_pin_states(STATE_IDLE, NULL) == Status_OK);
    CHECK(strstr(engine_output, "[PINSTATE:DOUT|relay|8|N|-|?]" ASCII_EOL) != NULL);
    return EXIT_SUCCESS;
}
