#include "support/pin_report_host.h"
#include "support/malloc_failure_host.h"
#include "check.h"

int main(void)
{
    prepare_pin_report();
    fail_malloc = true;
    CHECK(report_pins(STATE_IDLE, NULL) == Status_OK);
    fail_malloc = false;
    CHECK(failed_malloc_calls == 1);
    CHECK(pin_enumerations == 2);
    CHECK(strcmp(engine_output, "[PIN:PB3,Z step,z motor]" ASCII_EOL "[PIN:PA1,X step,x motor]" ASCII_EOL "[PIN:2,Y step]" ASCII_EOL) == 0);
    return EXIT_SUCCESS;
}
