#include "support/ipv4_settings_provider_host.h"
int main(void)
{
    prepare_ipv4_settings_provider();
    CHECK(system_command("$1001=192.0.2.42") == Status_OK);
    CHECK(strcmp(received_provider_ip, "192.0.2.42") == 0);
    CHECK(strcmp(saved_provider_ip, "192.0.2.42") == 0);
    CHECK(ip_set_calls == 1 && ip_save_calls == 1 && ip_change_calls == 1);
    CHECK(system_command("$1001") == Status_OK);
    CHECK(strstr(engine_output, "$1001=192.0.2.42" ASCII_EOL) != NULL);
    return EXIT_SUCCESS;
}
