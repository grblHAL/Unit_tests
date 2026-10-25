#include "at_host.h"
int main(void)
{
    at_prepare();
    at_load(WiFiMode_STA);
    *(ip_mode_t *)at_setting(Setting_IpMode3)->value = IpMode_Static;
    at_start();
    CHECK(at_command_seen("AT+CIPSTA=\"192.168.5.1\"\n"));
    CHECK(!at_command_seen("AT+CWDHCP") && at_command_seen("AT+CIPSERVER=1,23\n"));
    return 0;
}
