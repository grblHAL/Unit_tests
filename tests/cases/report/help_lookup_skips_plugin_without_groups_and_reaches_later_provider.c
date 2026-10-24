#include "support/second_settings_metadata_report_host.h"

static uint32_t counter_value;
static const setting_detail_t counter_setting = {
    .id = (setting_id_t)1201, .group = Group_General, .name = "Plugin counter",
    .datatype = Format_Integer, .type = Setting_NonCore, .value = &counter_value
};
static setting_details_t counter_details = {
    .n_settings = 1, .settings = &counter_setting,
    .load = metadata_persistence, .restore = metadata_persistence,
    .save = metadata_persistence
};

int main(void)
{
    prepare_metadata_report();
    CHECK(settings_register(&counter_details));
    CHECK(settings_register(&second_metadata_details));
    char topic[] = "seconddevice";
    CHECK(report_help(topic) == Status_OK);
    CHECK(strstr(engine_output, "---- Second device:") != NULL);
    CHECK(strstr(engine_output, "Second port limit") != NULL);
    CHECK(strstr(engine_output, "Plugin counter") == NULL);
    CHECK(strstr(engine_output, "N/A") == NULL);
    engine_output[0] = 0;
    char missing[] = "missingdevice";
    CHECK(report_help(missing) == Status_OK);
    CHECK(strcmp(engine_output, ASCII_EOL "N/A" ASCII_EOL) == 0);
    return EXIT_SUCCESS;
}
