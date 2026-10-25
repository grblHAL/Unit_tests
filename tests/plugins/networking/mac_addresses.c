#include "net_host.h"
int main(void)
{
    uint8_t mac[6] = {2, 0xAB, 0xCD, 1, 2, 3}, copy[6] = {0};
    CHECK(!strcmp(networking_mac_to_string(mac), "02:ab:cd:01:02:03"));
    char text[] = "02:AB:CD:01:02:03";
    CHECK(networking_string_to_mac(text, copy) && !memcmp(mac, copy, 6));
    char empty[] = "";
    CHECK(networking_string_to_mac(empty, copy) && networking_ismemnull(copy, 6) &&
          !*networking_mac_to_string(copy));
    CHECK(!bmac_eth_get(copy) && networking_ismemnull(copy, 6));
    CHECK(!bmac_wifi_get(copy));
    return 0;
}
