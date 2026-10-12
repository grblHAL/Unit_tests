#pragma once
#include "support/settings_report_host.h"
static unsigned plugin_value;
static bool unavailable_plugin_setting(const setting_detail_t *setting, uint_fast16_t offset)
{
    (void)setting;
    (void)offset;
    return false;
}
static const setting_detail_t plugin_report_settings[] = {
    {.id = (setting_id_t)1002, .name = "Visible second", .type = Setting_NonCore, .value = &plugin_value},
    {.id = (setting_id_t)1001, .name = "Visible first", .type = Setting_NonCore, .value = &plugin_value},
    {.id = (setting_id_t)1003, .name = "Hidden", .type = Setting_NonCore, .value = &plugin_value, .flags = {.hidden = true}},
    {.id = (setting_id_t)1004, .name = "Unavailable", .type = Setting_NonCore, .value = &plugin_value, .is_available = unavailable_plugin_setting}
};
static void plugin_settings_persistence(void) {}
static setting_details_t plugin_report_details = {.n_settings = 4, .settings = plugin_report_settings, .load = plugin_settings_persistence, .restore = plugin_settings_persistence, .save = plugin_settings_persistence};
static inline void prepare_plugin_settings_report(void)
{
    prepare_settings_report();
    CHECK(settings_register(&plugin_report_details));
}
