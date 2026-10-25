#include "at_host.h"
int main(void)
{
    at_prepare();
    at_controls(true);
    at_load(WiFiMode_AP);
    at_step(0);
    CHECK(at_control_writes == 3 && !at_commands[0] && at_pending() == 1);
    CHECK(at_control_ports[0] == 1 && at_control_levels[0]);
    CHECK(at_control_ports[1] == 0 && !at_control_levels[1]);
    CHECK(at_control_ports[2] == 0 && at_control_levels[2]);
    at_step(1500);
    CHECK(at_control_writes == 3 && at_command_seen("AT+CIPSERVER=1,23\n"));
    return 0;
}
