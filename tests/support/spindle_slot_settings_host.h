#pragma once
#include "support/multi_spindle_host.h"
static uint8_t secondary_spindle_setting = 2;
static setting_detail_t spindle_slot_setting[] = {
    {.id = (setting_id_t)(Setting_SpindleEnable0 + 1), .group = Group_Spindle,
     .name = "Secondary spindle", .type = Setting_NonCore, .datatype = Format_Int8,
     .value = &secondary_spindle_setting}
};
static void slot_settings_persistence(void) {}
static setting_details_t spindle_slot_details = {
    .n_settings = 1, .settings = spindle_slot_setting,
    .load = slot_settings_persistence, .restore = slot_settings_persistence,
    .save = slot_settings_persistence
};
static inline void prepare_settings_mapped_spindles(void)
{
    prepare_multi_spindle();
    CHECK(settings_register(&spindle_slot_details));
    CHECK(spindle_enable(1) == 1);
    CHECK(spindle_is_enabled(1) && spindle_get(1)->id == 1);
}
