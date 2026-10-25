#include "at_host.h"
int main(void)
{
    at_prepare();
    at_fail_command = "ATE0";
    at_fail_remaining = 1;
    at_load(WiFiMode_AP);
    at_start();
    CHECK(!strncmp(at_commands, "ATE0\nATE0\n", 10));
    CHECK(at_command_seen("AT+CIPSERVER=1,23\n") && at_pending() == 1 && !at_fail_remaining);
    return 0;
}
