#pragma once
#include "support/settings_host.h"
static char plugin_label[16] = "router", plugin_password[16] = "sample-key";
static char saved_plugin_label[16], saved_plugin_password[16];
static unsigned plugin_text_saves, plugin_text_changes;
static void save_plugin_text(void)
{
    strcpy(saved_plugin_label, plugin_label);
    strcpy(saved_plugin_password, plugin_password);
    plugin_text_saves++;
}
static void load_plugin_text(void) { }
static void restore_plugin_text(void)
{
    strcpy(plugin_label, "router");
    strcpy(plugin_password, "sample-key");
}
static void plugin_text_changed(settings_t *current, settings_changed_flags_t changed)
{
    CHECK(current == &settings);
    (void)changed;
    CHECK(strcmp(saved_plugin_label, plugin_label) == 0);
    CHECK(strcmp(saved_plugin_password, plugin_password) == 0);
    plugin_text_changes++;
}
static const setting_detail_t plugin_text_items[] = {
    {.id = (setting_id_t)1001, .group = Group_General, .name = "Node label",
     .type = Setting_NonCore, .datatype = Format_String, .format = "x(15)",
     .min_value = "0", .max_value = "15", .value = plugin_label},
    {.id = (setting_id_t)1002, .group = Group_General, .name = "Sample password",
     .type = Setting_NonCore, .datatype = Format_Password, .format = "x(15)",
     .min_value = "0", .max_value = "15", .value = plugin_password}
};
static setting_details_t plugin_text_details = {
    .n_settings = 2, .settings = plugin_text_items, .load = load_plugin_text,
    .restore = restore_plugin_text, .save = save_plugin_text, .on_changed = plugin_text_changed
};
static inline void prepare_plugin_text_settings(void)
{
    prepare_settings_store();
    CHECK(settings_register(&plugin_text_details));
}
