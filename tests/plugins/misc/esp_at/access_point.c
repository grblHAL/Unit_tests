#include "at_host.h"
int main(void)
{
    at_prepare();
    at_load(WiFiMode_AP);
    at_start();
    CHECK(at_command_seen("AT+CWMODE=2\n"));
    CHECK(at_command_seen("AT+CIPAP=\"192.168.5.1\"\n"));
    CHECK(at_command_seen("AT+CWSAP=\"grblHAL_AP\",\"grblHALpwd\",5,4,1,0\n"));
    CHECK(at_command_seen("AT+CIPSERVER=1,23\n") && at_pending() == 1 && at_claims == 1);
    grbl.on_report_options(false);
    CHECK(strstr(at_output, "[IP:192.168.5.1]") &&
          strstr(at_output, "[WIFI MAC:02:00:00:01:02:04]"));
    CHECK(strstr(at_output, "ESP-AT") && !strstr(at_output, "disabled"));
    return 0;
}
