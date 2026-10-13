#pragma once
#include "support/report_host.h"

static uint32_t channel_value;
static unsigned channel_mask = 6, reported_channels;
static setting_id_t channel_ids[3];
static bool channel_available(const setting_detail_t *setting, uint_fast16_t offset)
{
    (void)setting;
    return offset <= 4 && (channel_mask & (1u << (offset / 2))) != 0;
}
static const setting_detail_t channel_setting[] = {
    {.id = (setting_id_t)1001, .group = (setting_group_t)1000, .name = "Channel value",
     .type = Setting_NonCore, .datatype = Format_Integer, .value = &channel_value,
     .flags = {.increment = 2}, .is_available = channel_available}
};
static bool iterate_channels(const setting_detail_t *setting, setting_output_ptr callback, void *data)
{
    for(unsigned offset = 0; offset <= 4; offset += 2)
        if(channel_available(setting, offset) && !callback(setting, offset, data)) return false;
    return true;
}
static setting_id_t normalize_channel(setting_id_t id)
{
    return id >= 1001 && id <= 1005 && (id - 1001) % 2 == 0 ? (setting_id_t)1001 : 0;
}
static void channel_persistence(void) {}
static setting_details_t channel_details = {
    .n_settings = 1, .settings = channel_setting, .iterator = iterate_channels,
    .normalize = normalize_channel,
    .load = channel_persistence, .restore = channel_persistence, .save = channel_persistence
};
static bool capture_channel_setting(const setting_detail_t *setting, uint_fast16_t offset, void *data)
{
    CHECK(data == &reported_channels);
    if(setting->id == (setting_id_t)1001) {
        CHECK(reported_channels < 3);
        channel_ids[reported_channels++] = (setting_id_t)(setting->id + offset);
    }
    return true;
}
static inline void prepare_channel_settings_report(void)
{
    prepare_report();
    CHECK(settings_register(&channel_details));
    grbl.report.setting = capture_channel_setting;
}
