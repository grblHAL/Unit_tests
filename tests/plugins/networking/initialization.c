#include "net_host.h"
int main(void)
{
    net_prepare();
    networking_init();
    CHECK(net_registrations == 1);
    grbl.on_report_options(true);
    grbl.on_stream_changed();
    CHECK(net_previous_reports == 1 && net_previous_streams == 1 && !*net_output);
    return 0;
}
