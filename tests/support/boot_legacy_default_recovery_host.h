#pragma once
#include "support/boot_legacy_host.h"
#include "nvs_buffer.h"
#include "config.h"
static void invalidate_saved_settings_version(void)
{
    hal.nvs.put_byte(0, 0xff); // Same persistent marker as an erased/replaced store.
}
static inline void boot_with_unrecognized_saved_version(void)
{
    boot_during_init = invalidate_saved_settings_version;
    boot_program = "$I\n$100\n";
    run_legacy_boot_program();
    CHECK(boot_setup_calls == 1 && boot_release_calls == 0);
    CHECK(boot_reads == strlen(boot_program));
    CHECK(settings.version.id == SETTINGS_VERSION);
    NEAR(settings.axis[X_AXIS].steps_per_mm, DEFAULT_X_STEPS_PER_MM);
    char error[24];
    snprintf(error, sizeof(error), "error:%u" ASCII_EOL, (unsigned)Status_SettingReadFail);
    CHECK(strstr(engine_output, error) != NULL);
    CHECK(strstr(engine_output, "$100=") != NULL);
    nvs_buffer_sync_physical();
    settings_t saved;
    nvs_io_t *physical = nvs_buffer_get_physical();
    CHECK(physical->get_byte(0) == SETTINGS_VERSION);
    CHECK(physical->memcpy_from_nvs((uint8_t *)&saved, NVS_ADDR_GLOBAL, sizeof(saved), true) == NVS_TransferResult_OK);
    CHECK(saved.version.id == SETTINGS_VERSION);
    NEAR(saved.axis[X_AXIS].steps_per_mm, DEFAULT_X_STEPS_PER_MM);
}
