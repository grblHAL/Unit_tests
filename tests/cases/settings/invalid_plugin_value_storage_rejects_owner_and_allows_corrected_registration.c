#include "support/report_host.h"
static uint32_t first_value = 3, second_value = 7;
static setting_detail_t items[] = {
    {.id = (setting_id_t)1001, .group = Group_General, .name = "First",
     .datatype = Format_Integer, .type = Setting_NonCore, .value = NULL},
    {.id = (setting_id_t)1002, .group = Group_General, .name = "Second",
     .datatype = Format_Integer, .type = Setting_NonCore, .value = &second_value}
};
static void persist(void) {}
static setting_details_t details = {.n_settings = 2, .settings = items,
    .load = persist, .restore = persist, .save = persist};
int main(void)
{
    prepare_report();
    CHECK(!settings_register(&details));
    CHECK(setting_get_details((setting_id_t)1001, NULL) == NULL);
    CHECK(setting_get_details((setting_id_t)1002, NULL) == NULL);
    items[0].value = &first_value;
    CHECK(settings_register(&details));
    engine_output[0] = 0;
    report_grbl_settings(true, NULL);
    const char *first = strstr(engine_output, "$1001=3" ASCII_EOL);
    const char *second = strstr(engine_output, "$1002=7" ASCII_EOL);
    CHECK(first && second && first < second);
    CHECK(first_value == 3 && second_value == 7);
    return EXIT_SUCCESS;
}
