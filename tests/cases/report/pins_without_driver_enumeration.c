#include "support/report_host.h"
#include "check.h"

int main(void)
{
    prepare_report();
    CHECK(report_pins(STATE_IDLE, NULL) == Status_OK);
    CHECK(engine_output[0] == '\0');
    return EXIT_SUCCESS;
}
