#pragma once
#include "support/report_host.h"
static uint32_t metadata_value;
static bool metadata_unavailable(const setting_detail_t *setting, uint_fast16_t offset)
{
    (void)setting;
    (void)offset;
    return false;
}
static const setting_detail_t metadata_settings[] = {
    {.id = (setting_id_t)1002, .group = (setting_group_t)1000, .name = "Visible second", .datatype = Format_Integer, .type = Setting_NonCore, .value = &metadata_value},
    {.id = (setting_id_t)1001, .group = (setting_group_t)1000, .name = "Visible first", .datatype = Format_Integer, .type = Setting_NonCore, .value = &metadata_value},
    {.id = (setting_id_t)1003, .group = (setting_group_t)1000, .name = "Hidden setting", .datatype = Format_Integer, .type = Setting_NonCore, .value = &metadata_value, .flags = {.hidden = true}},
    {.id = (setting_id_t)1004, .group = (setting_group_t)1002, .name = "Unavailable setting", .datatype = Format_Integer, .type = Setting_NonCore, .value = &metadata_value, .is_available = metadata_unavailable},
    {.id = (setting_id_t)1005, .group = (setting_group_t)1001, .name = "Other group", .datatype = Format_Integer, .type = Setting_NonCore, .value = &metadata_value}
};
static const setting_group_detail_t metadata_groups[] = {
    {.id = (setting_group_t)1000, .parent = Group_General, .name = "Zulu fixture"},
    {.id = (setting_group_t)1001, .parent = Group_General, .name = "Alpha fixture"},
    {.id = (setting_group_t)1002, .parent = Group_General, .name = "Unavailable fixture"},
    {.id = (setting_group_t)1000, .parent = Group_General, .name = "Duplicate fixture"}
};
static void metadata_persistence(void) {}
static setting_details_t metadata_details = {
    .n_settings = 5, .settings = metadata_settings, .n_groups = 4, .groups = metadata_groups,
    .load = metadata_persistence, .restore = metadata_persistence, .save = metadata_persistence
};
static inline void prepare_metadata_report(void)
{
    prepare_report();
    CHECK(settings_register(&metadata_details));
    engine_output[0] = '\0';
}
