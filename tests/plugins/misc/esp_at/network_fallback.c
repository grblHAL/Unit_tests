#include "at_host.h"
static network_info_t other = {.interface = "other0"};
static unsigned requests;
static network_info_t *prior(const char *interface)
{
    CHECK(interface == other.interface);
    requests++;
    return &other;
}
int main(void)
{
    at_prepare();
    networking.get_info = prior;
    at_load(WiFiMode_AP);
    at_start();
    CHECK(networking.get_info(other.interface) == &other && requests == 1);
    network_info_t info;
    CHECK(at_network_info(&info).ip_aquired);
    CHECK(networking.get_info(info.interface) != &other && requests == 1);
    return 0;
}
