#include "support/report_host.h"
#include "support/ioports_host.h"
#include "check.h"
static float input_value_report(xbar_t *pin) { CHECK(pin->pin == 7); return 1; }

int main(void)
{
    prepare_report();
    register_ioports();
    xbar_t *pin = &digital_pins[Port_Input][0];
    pin->description = "door";
    pin->pin = 7;
    pin->mode.inverted = true;
    pin->mode.pull_mode = PullMode_Up;
    pin->mode.irq_mode = IRQ_Mode_Rising;
    pin->mode.debounce = true;
    pin->cap.invert = true;
    pin->cap.pull_mode = PullMode_UpDown;
    pin->cap.irq_mode = IRQ_Mode_All;
    pin->cap.debounce = true;
    pin->get_value = input_value_report;
    CHECK(report_pin_states(STATE_IDLE, NULL) == Status_OK);
    CHECK(strstr(engine_output, "[PINSTATE:DIN|door|7|IURD|IBAD|1]" ASCII_EOL) != NULL);
    return EXIT_SUCCESS;
}
