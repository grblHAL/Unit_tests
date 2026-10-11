#pragma once
#include "support/report_host.h"
static uint32_t human_metadata_value;
static setting_detail_t human_metadata_setting = {
    .id = (setting_id_t)1001, .group = Group_General, .name = "Fixture",
    .datatype = Format_Integer, .type = Setting_NonCore, .value = &human_metadata_value
};
static void human_metadata_persistence(void) {}
static setting_details_t human_metadata_details = {
    .n_settings = 1, .settings = &human_metadata_setting,
    .load = human_metadata_persistence, .restore = human_metadata_persistence,
    .save = human_metadata_persistence
};
static inline void prepare_human_metadata(void)
{
    prepare_report();
    CHECK(settings_register(&human_metadata_details));
    engine_output[0] = 0;
}
static inline void report_human_metadata(void)
{
    CHECK(report_settings_details(SettingsFormat_HumanReadable, (setting_id_t)1001, Group_All) == Status_OK);
}
