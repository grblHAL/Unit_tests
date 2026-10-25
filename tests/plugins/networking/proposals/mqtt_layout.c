#include "driver.h"
#include "networking.h"
#include <stddef.h>
#include <stdio.h>
int main(void)
{
    printf("mqtt_settings alignment=%zu ip offset=%zu\n", _Alignof(mqtt_settings_t),
           offsetof(mqtt_settings_t, ip));
    printf("network mqtt offset=%zu IPv4 alignment=%zu\n", offsetof(network_settings_t, mqtt),
           _Alignof(ip_addr_t));
    printf("embedded IP offset modulo alignment=%zu\n",
           (offsetof(network_settings_t, mqtt) + offsetof(mqtt_settings_t, ip)) %
               _Alignof(ip_addr_t));
    return 0;
}
