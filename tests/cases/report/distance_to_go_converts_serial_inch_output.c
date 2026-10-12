#include "support/report_motion_host.h"
#include "check.h"

int main(void)
{
    prepare_distance_report((coord_data_t){0}, (coord_data_t){.x=25.4f});
    settings.flags.report_inches = true;
    report_init();
    realtime_report();
    CHECK(strstr(engine_output, "|DTG:1.0000,0.0000,0.0000") != NULL);
    return EXIT_SUCCESS;
}
