#include "support/cycle_status_report_host.h"

int main(void)
{
    prepare_cycle_status_report();
    sys.probing_state = Probing_Active;
    realtime_report();
    CHECK(strncmp(engine_output, "<Run:2|", 7) == 0);
    engine_output[0] = '\0';
    sys.probing_state = Probing_Off;
    cycle_probe.triggered = true;
    realtime_report();
    CHECK(strncmp(engine_output, "<Run:2|", 7) == 0);
    engine_output[0] = '\0';
    cycle_probe.triggered = false;
    realtime_report();
    CHECK(strncmp(engine_output, "<Run|", 5) == 0);
    return EXIT_SUCCESS;
}
