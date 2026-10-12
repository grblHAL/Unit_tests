#include "support/report_host.h"
#include "support/ioports_host.h"
#include <stdio.h>
#include "check.h"

int main(void)
{
    prepare_report();
    register_ioports();
    xbar_t *pin = &digital_pins[Port_Input][0];
    pin->description = "door";
    pin->pin = 7;
    const pin_irq_mode_t modes[] = {IRQ_Mode_None, IRQ_Mode_Rising, IRQ_Mode_Falling, IRQ_Mode_RisingFalling, IRQ_Mode_Change, IRQ_Mode_Edges, IRQ_Mode_High, IRQ_Mode_Low, IRQ_Mode_All};
    const char codes[] = "-RFTCEHLA";
    for(unsigned i = 0; i < sizeof(modes) / sizeof(modes[0]); i++) {
        pin->mode.irq_mode = pin->cap.irq_mode = modes[i];
        engine_output[0] = 0;
        CHECK(report_pin_states(STATE_IDLE, NULL) == Status_OK);
        char expected[96];
        snprintf(expected, sizeof(expected), "[PINSTATE:DIN|door|7|N-%c-|--%c-|?]" ASCII_EOL, codes[i], codes[i]);
        CHECK(strstr(engine_output, expected) != NULL);
    }
    return EXIT_SUCCESS;
}
