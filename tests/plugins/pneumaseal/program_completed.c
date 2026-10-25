#include "seal_host.h"
int main(void)
{
    seal_start();
    seal_spindle(true);
    live_spindle = false;
    grbl.on_program_completed((program_flow_t)0, false);
    CHECK(solenoid && timer_ms == 120000);
    seal_expire();
    CHECK(!solenoid);
    return 0;
}
