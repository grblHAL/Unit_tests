#include "seal_host.h"
int main(void)
{
    seal_start();
    unsigned prev = chains;
    seal_state(STATE_CYCLE);
    seal_spindle(true);
    hal.driver_reset();
    grbl.on_program_completed((program_flow_t)0, false);
    grbl.on_report_options(true);
    grbl.on_report_options(false);
    CHECK(chains == prev + 7);
    return 0;
}
