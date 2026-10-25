#include "at_host.h"
int main(void)
{
    at_prepare();
    at_existing_server = true;
    at_load(WiFiMode_AP);
    at_fail_command = "AT+CIPSERVER=0,1";
    at_fail_remaining = 1;
    at_start();
    network_info_t info;
    network_flags_t flags = at_network_info(&info);
    CHECK(!flags.interface_up && !flags.ip_aquired && !at_pending());
    CHECK(!at_command_seen("AT+CWMODE"));
    return 0;
}
