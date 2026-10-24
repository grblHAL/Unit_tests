#include "webui_host.h"
int main(void)
{
    char ip[] = "IP=192.168.1.42", gw[] = "GW=192.168.1.1", mask[] = "MSK=255.255.255.0";
    char *argv[] = {ip, gw, mask, NULL};
    CHECK(strcmp(webui_get_arg(3, argv, "IP="), "192.168.1.42") == 0);
    CHECK(strcmp(webui_get_arg(3, argv, "GW="), "192.168.1.1") == 0);
    CHECK(strcmp(webui_get_arg(3, argv, "MSK="), "255.255.255.0") == 0);
    return 0;
}
