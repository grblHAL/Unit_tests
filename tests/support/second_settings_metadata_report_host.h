#pragma once
#include "support/settings_metadata_report_host.h"
static uint32_t second_metadata_value;
static const setting_detail_t second_metadata_settings[] = {
    {.id = (setting_id_t)1101, .group = (setting_group_t)1100, .name = "Second port limit", .datatype = Format_Integer, .type = Setting_NonCore, .value = &second_metadata_value}
};
static const setting_group_detail_t second_metadata_groups[] = {
    {.id = (setting_group_t)1100, .parent = Group_General, .name = "Second device"}
};
static setting_details_t second_metadata_details = {
    .n_settings = 1, .settings = second_metadata_settings,
    .n_groups = 1, .groups = second_metadata_groups,
    .load = metadata_persistence, .restore = metadata_persistence, .save = metadata_persistence
};
static inline void prepare_second_metadata_report(void)
{
    prepare_metadata_report();
    CHECK(settings_register(&second_metadata_details));
}
