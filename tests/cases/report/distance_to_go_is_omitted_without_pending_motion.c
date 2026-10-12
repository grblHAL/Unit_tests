#include "support/report_host.h"
#include "check.h"

int main(void)
{
    prepare_report();
    settings.status_report.distance_to_go = true;
    CHECK(plan_get_current_block() == NULL);
    realtime_report();
    CHECK(strstr(engine_output, "|DTG:") == NULL);
    return EXIT_SUCCESS;
}
