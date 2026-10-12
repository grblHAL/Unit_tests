#include "support/report_host.h"
#include "check.h"

int main(void)
{
    prepare_report();
    char offset[] = "G10L2P1X4";
    CHECK(gc_execute_block(offset) == Status_OK);
    sys.position[X_AXIS] = 80;
    sync_position();
    float target[N_AXIS] = {10,0,0};
    plan_line_data_t data;
    plan_data_init(&data);
    data.feed_rate = 100;
    CHECK(plan_buffer_line(target, &data));
    settings.status_report.distance_to_go = true;
    settings.status_report.machine_position = false;
    realtime_report();
    CHECK(strstr(engine_output, "|WPos:-3.000,0.000,0.000") != NULL);
    CHECK(strstr(engine_output, "|DTG:9.000,0.000,0.000") != NULL);
    return EXIT_SUCCESS;
}
