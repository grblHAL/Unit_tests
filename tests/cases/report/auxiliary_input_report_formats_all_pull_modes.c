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
    const pull_mode_t modes[] = {PullMode_None, PullMode_Up, PullMode_Down, PullMode_UpDown};
    const char codes[] = "-UDB";
    for(unsigned i = 0; i < sizeof(modes) / sizeof(modes[0]); i++) {
        pin->mode.pull_mode = pin->cap.pull_mode = modes[i];
        engine_output[0] = 0;
        CHECK(report_pin_states(STATE_IDLE, NULL) == Status_OK);
        char expected[96];
        snprintf(expected, sizeof(expected), "[PINSTATE:DIN|door|7|N%c--|-%c--|?]" ASCII_EOL, codes[i], codes[i]);
        CHECK(strstr(engine_output, expected) != NULL);
    }
    return EXIT_SUCCESS;
}
