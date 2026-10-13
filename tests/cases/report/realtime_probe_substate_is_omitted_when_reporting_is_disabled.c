#include "support/cycle_status_report_host.h"

int main(void)
{
    prepare_cycle_status_report();
    settings.status_report.run_substate = false;
    sys.probing_state = Probing_Active;
    realtime_report();
    CHECK(strncmp(engine_output, "<Run|", 5) == 0);
    return EXIT_SUCCESS;
}
