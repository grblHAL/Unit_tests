#include "support/report_host.h"
static uint32_t first_value = 3, second_value = 7;
static unsigned persistence_calls, setter_calls;
static setting_detail_t items[] = {
    {.id = (setting_id_t)1001, .group = (setting_group_t)1000, .name = "First",
     .datatype = Format_Integer, .type = Setting_NonCore, .value = &first_value},
    {.id = (setting_id_t)1002, .group = (setting_group_t)1000, .name = "Second",
     .datatype = Format_Integer, .type = Setting_NonCore, .value = &second_value}
};
static setting_group_detail_t group = {.id = (setting_group_t)1000, .parent = Group_General, .name = "Plugin"};
static setting_descr_t description = {.id = (setting_id_t)1001, .description = "First value"};
static void persist(void) { persistence_calls++; }
static status_code_t set_value(setting_id_t id, uint_fast16_t value)
{
    CHECK(id == (setting_id_t)1001);
    setter_calls++;
    first_value = value;
    return Status_OK;
}
static setting_details_t details = {.n_settings = 2, .settings = items,
    .n_groups = 1, .groups = &group, .n_descriptions = 1, .descriptions = &description,
    .load = persist, .restore = persist, .save = persist};
static void expect_rejected(void)
{
    CHECK(!settings_register(&details));
    CHECK(setting_get_details((setting_id_t)1001, NULL) == NULL);
    CHECK(setting_get_details((setting_id_t)1002, NULL) == NULL);
    CHECK(setting_get_group_details((setting_group_t)1000) == NULL);
    CHECK(persistence_calls == 0 && setter_calls == 0);
    CHECK(first_value == 3 && second_value == 7);
}
int main(void)
{
    prepare_report();
    details.load = NULL; expect_rejected(); details.load = persist;
    details.restore = NULL; expect_rejected(); details.restore = persist;
    details.save = NULL; expect_rejected(); details.save = persist;
    items[0].type = (setting_type_t)(Setting_MaxType + 1);
    expect_rejected(); items[0].type = Setting_NonCore;
    items[0].value = NULL; expect_rejected(); items[0].value = &first_value;
    items[1].value = NULL; expect_rejected(); items[1].value = &second_value;
    items[0].type = Setting_NonCoreFn;
    items[0].value = (void *)set_value;
    expect_rejected();
    items[0].type = Setting_NonCore; items[0].value = &first_value;
    description.description = NULL; expect_rejected(); description.description = "First value";
    group.name = NULL; expect_rejected(); group.name = "Plugin";
    group.parent = group.id; expect_rejected(); group.parent = Group_General;
    CHECK(settings_register(&details));
    CHECK(setting_get_group_details(group.id) == &group);
    CHECK(strcmp(setting_get_description((setting_id_t)1001), "First value") == 0);
    engine_output[0] = 0;
    report_grbl_settings(true, NULL);
    const char *first = strstr(engine_output, "$1001=3" ASCII_EOL);
    const char *second = strstr(engine_output, "$1002=7" ASCII_EOL);
    CHECK(first && second && first < second);
    CHECK(first_value == 3 && second_value == 7);
    CHECK(persistence_calls == 0 && setter_calls == 0);
    return EXIT_SUCCESS;
}
