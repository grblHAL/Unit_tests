#include "support/report_motion_host.h"
#include "check.h"

int main(void)
{
    prepare_distance_report((coord_data_t){.values={1,-2,3}}, (coord_data_t){.values={10,4,2}});
    realtime_report();
    CHECK(strstr(engine_output, "|MPos:1.000,-2.000,3.000") != NULL);
    CHECK(strstr(engine_output, "|DTG:9.000,6.000,-1.000") != NULL);
    return EXIT_SUCCESS;
}
