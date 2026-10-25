#include "net_host.h"
int main(void)
{
    char client_id[sizeof(net_infos[0].mqtt_client_id)];
    networking_make_mqtt_clientid("02:00:00:01:02:03", client_id);
    CHECK(strcmp(client_id, "grblHAL.010203") == 0);
    networking_make_mqtt_clientid("02:AA:BB:CC:DD:EE", client_id);
    CHECK(strcmp(client_id, "grblHAL.CCDDEE") == 0);
    networking_make_mqtt_clientid("", client_id);
    CHECK(strcmp(client_id, "grblHAL") == 0);
    return 0;
}
