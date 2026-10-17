#pragma once
#include "support/settings_host.h"
static struct numeric_values {
    float decimal;
    uint8_t axes;
    uint8_t byte;
    uint16_t word;
    uint32_t integer;
    uint8_t enabled;
} numeric_live = {.decimal = 1.25f, .axes = X_AXIS_BIT, .byte = 7, .word = 1000, .integer = 123456, .enabled = 1}, numeric_saved;
static unsigned numeric_saves, numeric_notifications;
static void numeric_save(void) { numeric_saved = numeric_live; numeric_saves++; }
static void numeric_load(void) { numeric_live = numeric_saved; }
static void numeric_restore(void)
{
    numeric_live = (struct numeric_values){0};
    numeric_save(); /* Registered owners persist their own restored defaults. */
}
static void numeric_changed(settings_t *current, settings_changed_flags_t changes)
{
    CHECK(current == &settings);
    (void)changes;
    NEAR(numeric_saved.decimal, numeric_live.decimal);
    CHECK(numeric_saved.axes == numeric_live.axes && numeric_saved.byte == numeric_live.byte);
    CHECK(numeric_saved.word == numeric_live.word && numeric_saved.integer == numeric_live.integer);
    CHECK(numeric_saved.enabled == numeric_live.enabled);
    numeric_notifications++;
}
static const setting_detail_t numeric_settings[] = {
    {.id = (setting_id_t)1001, .group = Group_General, .name = "Plugin gain", .type = Setting_NonCore,
     .datatype = Format_Decimal, .format = "0.000", .min_value = "0", .max_value = "1000", .value = &numeric_live.decimal},
    {.id = (setting_id_t)1002, .group = Group_General, .name = "Plugin axes", .type = Setting_NonCore,
     .datatype = Format_AxisMask, .value = &numeric_live.axes},
    {.id = (setting_id_t)1003, .group = Group_General, .name = "Plugin byte", .type = Setting_NonCore,
     .datatype = Format_Int8, .min_value = "0", .max_value = "255", .value = &numeric_live.byte},
    {.id = (setting_id_t)1004, .group = Group_General, .name = "Plugin word", .type = Setting_NonCore,
     .datatype = Format_Int16, .min_value = "0", .max_value = "65535", .value = &numeric_live.word},
    {.id = (setting_id_t)1005, .group = Group_General, .name = "Plugin counter", .type = Setting_NonCore,
     .datatype = Format_Integer, .min_value = "0", .max_value = "4294967295", .value = &numeric_live.integer},
    {.id = (setting_id_t)1006, .group = Group_General, .name = "Plugin enabled", .type = Setting_NonCore,
     .datatype = Format_Bool, .value = &numeric_live.enabled}
};
static setting_details_t numeric_details = {.n_settings = 6, .settings = numeric_settings,
    .save = numeric_save, .load = numeric_load, .restore = numeric_restore, .on_changed = numeric_changed};
static inline void prepare_numeric_plugin(void)
{
    prepare_settings_store();
    numeric_saved = numeric_live;
    CHECK(settings_register(&numeric_details));
}
static inline void check_numeric_storage(unsigned offset, const char *text, uint32_t expected)
{
    prepare_numeric_plugin();
    setting_id_t id = (setting_id_t)(1001 + offset);
    status_code_t status = store_setting(id, text);
    if(status != Status_OK) fprintf(stderr, "Plugin setting %u value %s returned status %u\n", (unsigned)id, text, (unsigned)status);
    CHECK(status == Status_OK);
    const setting_detail_t *detail = setting_get_details(id, NULL);
    CHECK(detail != NULL);
    CHECK(setting_get_int_value(detail, 0) == expected);
    CHECK(strcmp(setting_get_value(detail, 0), text) == 0);
    CHECK(numeric_saves == 1 && numeric_notifications == 1);
    NEAR(numeric_live.decimal, 1.25f);
    CHECK(numeric_live.axes == (offset == 1 ? expected : X_AXIS_BIT));
    CHECK(numeric_live.byte == (offset == 2 ? expected : 7));
    CHECK(numeric_live.word == (offset == 3 ? expected : 1000));
    CHECK(numeric_live.integer == (offset == 4 ? expected : 123456));
}

static inline void check_numeric_rejection(unsigned offset, const char *text)
{
    prepare_numeric_plugin();
    CHECK(store_setting((setting_id_t)(1001 + offset), text) == Status_SettingValueOutOfRange);
    CHECK(numeric_saves == 0 && numeric_notifications == 0);
    NEAR(numeric_live.decimal, 1.25f);
    CHECK(numeric_live.axes == X_AXIS_BIT && numeric_live.byte == 7);
    CHECK(numeric_live.word == 1000 && numeric_live.integer == 123456 && numeric_live.enabled == 1);
    CHECK(numeric_saved.axes == numeric_live.axes && numeric_saved.byte == numeric_live.byte);
    CHECK(numeric_saved.word == numeric_live.word && numeric_saved.integer == numeric_live.integer);
}
