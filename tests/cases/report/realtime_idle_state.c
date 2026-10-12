#include "support/report_host.h"
#include "state_machine.h"
#include "check.h"

int main(void)
{
    prepare_report();
    state_set(STATE_IDLE);
    realtime_report();
    CHECK(strcmp(engine_output, "<Idle|WPos:0.000,0.000,0.000>" ASCII_EOL) == 0);
    return EXIT_SUCCESS;
}
