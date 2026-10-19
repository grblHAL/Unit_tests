#pragma once
#include "support/system_command_host.h"
static char provider_ip[16] = "192.0.2.1", saved_provider_ip[16], received_provider_ip[32];
static unsigned ip_set_calls, ip_save_calls, ip_change_calls;
static status_code_t ip_driver_status = Status_OK;
static status_code_t provider_set_ip(setting_id_t id, char *value)
{
    CHECK(id == (setting_id_t)1001 && strlen(value) < sizeof(received_provider_ip));
    strcpy(received_provider_ip, value);
    ip_set_calls++;
    if(ip_driver_status == Status_OK) {
        CHECK(strlen(value) < sizeof(provider_ip));
        strcpy(provider_ip, value);
    }
    return ip_driver_status;
}
static char *provider_get_ip(setting_id_t id) { CHECK(id == (setting_id_t)1001); return provider_ip; }
static void provider_save_ip(void) { strcpy(saved_provider_ip, provider_ip); ip_save_calls++; }
static void provider_load_ip(void) { strcpy(provider_ip, saved_provider_ip); }
static void provider_restore_ip(void) { strcpy(provider_ip, "192.0.2.1"); provider_save_ip(); }
static void provider_ip_changed(settings_t *current, settings_changed_flags_t changed)
{
    CHECK(current == &settings);
    (void)changed;
    CHECK(strcmp(provider_ip, saved_provider_ip) == 0);
    ip_change_calls++;
}
static const setting_detail_t provider_ip_setting[] = {
    {.id = (setting_id_t)1001, .group = Group_General, .name = "Network address",
     .type = Setting_NonCoreFn, .datatype = Format_IPv4,
     .value = (void *)provider_set_ip, .get_value = (void *)provider_get_ip}
};
static setting_details_t provider_ip_details = {.n_settings = 1, .settings = provider_ip_setting,
    .save = provider_save_ip, .load = provider_load_ip, .restore = provider_restore_ip,
    .on_changed = provider_ip_changed};
static inline void prepare_ipv4_settings_provider(void)
{
    prepare_system_command();
    strcpy(saved_provider_ip, provider_ip);
    CHECK(settings_register(&provider_ip_details));
}
