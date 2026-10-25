#include "homing_host.h"
grbl_hal_t hal;
grbl_t grbl;
system_t sys;
settings_t settings;
setting_details_t *registered_settings;
unsigned calls[N_AXIS], rate_calls, complete_calls, settings_calls, options, saves;
float acceleration[N_AXIS];
bool alloc_ok = true, accept_override = true;
static uint8_t nvs[128];
static size_t stored;
nvs_address_t nvs_alloc(size_t size)
{
    CHECK(size <= sizeof(nvs));
    return alloc_ok ? 2048 : 0;
}
static nvs_transfer_result_t read_nvs(uint8_t *dst, uint32_t addr, uint32_t size, bool checksum)
{
    CHECK(addr == 2048 && checksum && size <= sizeof(nvs));
    if (!stored)
        return false;
    CHECK(size == stored);
    memcpy(dst, nvs, size);
    return true;
}
static nvs_transfer_result_t write_nvs(uint32_t addr, uint8_t *src, uint32_t size, bool checksum)
{
    CHECK(addr == 2048 && checksum && size <= sizeof(nvs));
    memcpy(nvs, src, size);
    stored = size;
    saves++;
    return true;
}
bool settings_register(setting_details_t *details)
{
    CHECK(!registered_settings);
    registered_settings = details;
    return true;
}
setting_id_t settings_get_axis_base(setting_id_t id, uint_fast8_t *idx)
{
    // Model the documented public 280.. axis-setting family only.
    for (unsigned i = 0; i < N_AXIS; i++)
        if (id == Setting_AxisExtended8 + i)
        {
            *idx = i;
            return Setting_AxisExtended8;
        }
    *idx = 0;
    return Setting_SettingsMax;
}
bool settings_override_acceleration(uint8_t axis, float value)
{
    CHECK(axis < N_AXIS);
    calls[axis]++;
    if (!accept_override)
        return false;
    acceleration[axis] = value;
    return true;
}
void report_plugin(const char *name, const char *version)
{
    CHECK(strcmp(name, "Sienci Homing Acceleration Plugin") == 0 && strcmp(version, "0.01") == 0);
    options++;
}
static void previous_rate(axes_signals_t axes, coord_data_t *feedrate, homing_mode_t mode)
{
    CHECK(axes.mask && feedrate);
    (void)mode;
    rate_calls++;
}
static void previous_complete(axes_signals_t axes, bool success)
{
    CHECK(axes.mask);
    (void)success;
    complete_calls++;
}
static void previous_settings(settings_t *s, settings_changed_flags_t changed)
{
    CHECK(s == &settings);
    (void)changed;
    settings_calls++;
}
static const char *previous_unit(setting_id_t id, uint_fast8_t axis)
{
    (void)id;
    CHECK(axis < N_AXIS);
    return "previous";
}
static void previous_options(bool newopt)
{
    (void)newopt;
    options++;
}
void ha_prepare(bool chain)
{
    hal.nvs.memcpy_from_nvs = read_nvs;
    hal.nvs.memcpy_to_nvs = write_nvs;
    for (unsigned i = 0; i < N_AXIS; i++)
        settings.axis[i].acceleration = (i + 1) * 36000.0f;
    grbl.on_report_options = previous_options;
    if (chain)
    {
        grbl.on_homing_rate_set = previous_rate;
        grbl.on_homing_completed = previous_complete;
        grbl.on_settings_changed = previous_settings;
        grbl.on_set_axis_setting_unit = previous_unit;
    }
}
void ha_start(bool chain)
{
    ha_prepare(chain);
    homing_accel_init();
    CHECK(registered_settings && registered_settings->n_settings == 1);
    registered_settings->load();
}
void ha_set(unsigned axis, float value)
{
    CHECK(axis < N_AXIS);
    const setting_detail_t *s = registered_settings->settings;
    CHECK(((setting_set_float_ptr)s->value)((setting_id_t)(Setting_AxisExtended8 + axis), value) ==
          Status_OK);
}
float ha_get(unsigned axis)
{
    CHECK(axis < N_AXIS);
    const setting_detail_t *s = registered_settings->settings;
    return ((setting_get_float_ptr)s->get_value)((setting_id_t)(Setting_AxisExtended8 + axis));
}
void ha_rate(uint8_t mask)
{
    axes_signals_t axes = {.mask = mask};
    coord_data_t feedrate = {0};
    grbl.on_homing_rate_set(axes, &feedrate, (homing_mode_t)0);
}
void ha_complete(uint8_t mask, bool success)
{
    axes_signals_t axes = {.mask = mask};
    grbl.on_homing_completed(axes, success);
}
