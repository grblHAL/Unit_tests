#include "at_host.h"
int main(void)
{
    at_prepare();
    at_load(WiFiMode_AP);
    at_start();
    at_output[0] = 0;
    CHECK(at_command_seen("AT+CIPSERVER=1,23\n") && at_netif() == Status_OK);
    printf("NETIF response: %s\n", at_output);
    CHECK(strstr(at_output, "Listening=23"));
    return 0;
}
