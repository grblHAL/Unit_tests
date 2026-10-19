#include "support/ipv4_settings_provider_host.h"
int main(void)
{
    prepare_ipv4_settings_provider();
    ip_driver_status = Status_SettingValueOutOfRange;
    CHECK(system_command("$1001=bad-address") == Status_SettingValueOutOfRange);
    CHECK(ip_set_calls == 1 && strcmp(received_provider_ip, "bad-address") == 0);
    CHECK(ip_save_calls == 0 && ip_change_calls == 0);
    CHECK(strcmp(provider_ip, "192.0.2.1") == 0 && strcmp(saved_provider_ip, "192.0.2.1") == 0);
    CHECK(system_command("$1001") == Status_OK);
    CHECK(strstr(engine_output, "$1001=192.0.2.1" ASCII_EOL) != NULL);
    return EXIT_SUCCESS;
}
