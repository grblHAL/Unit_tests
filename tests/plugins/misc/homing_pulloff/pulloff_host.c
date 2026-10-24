#include "pulloff_host.h"
#include <string.h>
grbl_hal_t hal;
grbl_t grbl;
settings_t settings;
setting_details_t *details;
bool allocation_ok = true, registration_ok = true;
unsigned saves, updates, chained_changes, options, reports;
settings_changed_flags_t last_flags;
coord_data_t requested;
static uint8_t nvs[sizeof(coord_data_t)];
static size_t stored;
nvs_address_t nvs_alloc(size_t size)
{
    CHECK(size == sizeof(nvs));
    return allocation_ok ? 2048 : 0;
}
static nvs_transfer_result_t read_nvs(uint8_t *dst, uint32_t address, uint32_t size, bool checksum)
{
    CHECK(address == 2048 && size == sizeof(nvs) && checksum);
    if (!stored)
        return false;
    memcpy(dst, nvs, size);
    return true;
}
static nvs_transfer_result_t write_nvs(uint32_t address, uint8_t *src, uint32_t size, bool checksum)
{
    CHECK(address == 2048 && size == sizeof(nvs) && checksum);
    memcpy(nvs, src, size);
    stored = size;
    saves++;
    return true;
}
bool settings_register(setting_details_t *settings_details)
{
    CHECK(!details);
    if (registration_ok)
        details = settings_details;
    return registration_ok;
}
setting_id_t settings_get_axis_base(setting_id_t id, uint_fast8_t *axis)
{
    // Only the documented 290.. per-axis plugin setting family is modeled here.
    for (unsigned i = 0; i < N_AXIS; i++)
        if (id == Setting_AxisExtended9 + i)
        {
            *axis = i;
            return Setting_AxisExtended9;
        }
    *axis = 0;
    return Setting_SettingsMax;
}
coord_data_t *limits_homing_pulloff(coord_data_t *distance)
{
    CHECK(distance);
    requested = *distance;
    updates++;
    return &requested;
}
static void changed(settings_t *value, settings_changed_flags_t flags)
{
    CHECK(value == &settings);
    last_flags = flags;
    chained_changes++;
}
static void report_options(bool newopt)
{
    (void)newopt;
    options++;
}
void report_plugin(const char *name, const char *version)
{
    CHECK(strcmp(name, "Homing pulloff") == 0 && strcmp(version, "0.02") == 0);
    reports++;
}
void prepare_pulloff(void)
{
    settings.homing.pulloff = 2;
    hal.nvs.memcpy_from_nvs = read_nvs;
    hal.nvs.memcpy_to_nvs = write_nvs;
    grbl.on_settings_changed = changed;
    grbl.on_report_options = report_options;
}
void initialize_pulloff(void)
{
    void homing_pulloff_init(void);
    homing_pulloff_init();
}
void load_pulloff(void)
{
    prepare_pulloff();
    initialize_pulloff();
    CHECK(details && details->n_settings == 1);
    details->load();
}
void set_pulloff(unsigned axis, float value)
{
    CHECK(axis < N_AXIS);
    const setting_detail_t *s = details->settings;
    CHECK(((setting_set_float_ptr)s->value)(Setting_AxisExtended9 + axis, value) == Status_OK);
}
float get_pulloff(unsigned axis)
{
    CHECK(axis < N_AXIS);
    const setting_detail_t *s = details->settings;
    return ((setting_get_float_ptr)s->get_value)(Setting_AxisExtended9 + axis);
}
