#include "support/cycle_status_report_host.h"

int main(void)
{
    prepare_cycle_status_report();
    sys.probing_state = Probing_Active;
    sys.flags.feed_hold_pending = true;
    realtime_report();
    CHECK(strncmp(engine_output, "<Run:1|", 7) == 0);
    engine_output[0] = '\0';
    sys.flags.feed_hold_pending = false;
    realtime_report();
    CHECK(strncmp(engine_output, "<Run:2|", 7) == 0);
    return EXIT_SUCCESS;
}
