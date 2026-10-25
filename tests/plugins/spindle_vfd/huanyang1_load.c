#include "huanyang1_host.h"
#include <string.h>
static char output[64];
static void capture(const char *text)
{
    CHECK(strlen(output) + strlen(text) < sizeof(output));
    strcat(output, text);
}
int main(void)
{

    vfd_prepare(true);
    vfd_start();
    CHECK(grbl.on_realtime_report);
    vfd_ticks = 150;
    vfd_motor->get_state(vfd_motor);
    grbl.on_realtime_report(capture, (report_tracking_flags_t){0});
    CHECK(strcmp(output, "|Sl:25.0") == 0);
    output[0] = 0;
    grbl.on_realtime_report(capture, (report_tracking_flags_t){0});
    CHECK(!*output);
    vfd_amps = 50;
    vfd_ticks = 300;
    vfd_motor->get_state(vfd_motor);
    grbl.on_realtime_report(capture, (report_tracking_flags_t){.all = On});
    CHECK(strcmp(output, "|Sl:50.0") == 0);
    return 0;
}
