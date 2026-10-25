#include "at_host.h"
int main(void)
{
    at_prepare();
    at_load(WiFiMode_AP);
    at_fail_command = "AT+CWSAP=\"grblHAL_AP\",\"grblHALpwd\",5,4,1,0";
    at_fail_remaining = 1;
    at_start();
    CHECK(!at_pending() && !at_command_seen("AT+CIPSERVER=1,23\n"));
    grbl.on_report_options(false);
    CHECK(strstr(at_output, "ESP-AT (disabled)"));
    return 0;
}
