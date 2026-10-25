#include "at_host.h"
int main(void)
{
    at_prepare();
    at_controls(false);
    at_load(WiFiMode_AP);
    at_start();
    CHECK(!at_control_writes && at_command_seen("AT+CIPSERVER=1,23\n") && at_pending() == 1);
    return 0;
}
