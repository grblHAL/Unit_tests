#pragma once
#include "support/report_host.h"
static unsigned report_setting_count;
static setting_id_t reported_setting_ids[512];
static bool capture_setting_id(const setting_detail_t *setting, uint_fast16_t offset, void *data)
{
    (void)offset;
    CHECK(data == &report_setting_count);
    CHECK(report_setting_count < 512);
    reported_setting_ids[report_setting_count++] = setting->id;
    return true;
}
static bool saw_setting(setting_id_t id)
{
    for(unsigned i = 0; i < report_setting_count; i++) if(reported_setting_ids[i] == id) return true;
    return false;
}
static inline void prepare_settings_report(void)
{
    prepare_report();
    grbl.report.setting = capture_setting_id;
}
