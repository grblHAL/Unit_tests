#include "support/pin_report_host.h"
#include "check.h"

int main(void)
{
    prepare_pin_report();
    CHECK(report_pins(STATE_IDLE, NULL) == Status_OK);
    CHECK(strcmp(engine_output, "[PIN:PA1,X step,x motor]" ASCII_EOL
                               "[PIN:2,Y step]" ASCII_EOL
                               "[PIN:PB3,Z step,z motor]" ASCII_EOL) == 0);
    CHECK(pin_enumerations == 2);
    return EXIT_SUCCESS;
}
