#pragma once
#include "support/human_metadata_report_host.h"
static const setting_descr_t description_metadata[] = {
    {.id = (setting_id_t)1001, .description = "First\\nSecond\\nThird"}
};
static setting_details_t description_details = {
    .n_settings = 1, .settings = &human_metadata_setting,
    .n_descriptions = 1, .descriptions = description_metadata,
    .load = human_metadata_persistence, .restore = human_metadata_persistence,
    .save = human_metadata_persistence
};
static void description_write_n(const uint8_t *data, uint16_t length)
{
    size_t used = strlen(engine_output); CHECK(used + length < sizeof(engine_output));
    memcpy(engine_output + used, data, length); engine_output[used + length] = 0;
}
static inline void prepare_description_metadata(void)
{
    prepare_report(); CHECK(settings_register(&description_details));
    hal.stream.write_n = description_write_n; engine_output[0] = 0;
}
