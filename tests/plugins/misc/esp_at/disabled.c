#include "at_host.h"
int main(void)
{
    at_prepare();
    at_load(WiFiMode_NULL);
    at_start();
    CHECK(!at_pending() && !at_command_seen("AT+CWMODE") && !at_command_seen("AT+CIPSERVER=1,"));
    grbl.on_report_options(true);
    CHECK(at_reports == 1 && !at_output[0]);
    grbl.on_report_options(false);
    CHECK(at_reports == 2 && strstr(at_output, "ESP-AT (disabled)"));
    return 0;
}
