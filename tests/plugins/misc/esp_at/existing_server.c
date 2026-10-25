#include "at_host.h"
int main(void)
{
    at_prepare();
    at_existing_server = true;
    at_load(WiFiMode_AP);
    at_start();
    const char *stop = strstr(at_commands, "AT+CIPSERVER=0,1\n");
    const char *start = strstr(at_commands, "AT+CIPSERVER=1,23\n");
    CHECK(stop && start && stop < start && at_pending() == 1);
    return 0;
}
