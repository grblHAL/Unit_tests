#include "at_host.h"
int main(void)
{
    at_prepare();
    at_load(WiFiMode_STA);
    at_start();
    CHECK(at_command_seen("AT+CWMODE=1,0\n") && at_command_seen("AT+CWDHCP=1,1\n"));
    CHECK(at_command_seen("AT+CWJAP=\"Shop\",\"fixturepass\"\n"));
    CHECK(at_command_seen("AT+CIPSERVER=1,23\n") && at_pending() == 1);
    grbl.on_report_options(false);
    CHECK(strstr(at_output, "[IP:192.168.5.20]") && strstr(at_output, "02:00:00:01:02:03"));
    CHECK(!strstr(at_output, "disabled"));
    return 0;
}
