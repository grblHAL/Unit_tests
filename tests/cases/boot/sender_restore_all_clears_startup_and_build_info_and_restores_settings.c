#include "support/boot_host.h"
#include "nvs_buffer.h"
static void seed_custom_records(void)
{
    settings.arc_tolerance = 0.1f;
    settings_write_global();
    CHECK(settings_write_build_info("Workshop router"));
    stored_line_t startup = "G21";
    settings_write_startup_line(0, startup);
    stored_line_t verified;
    CHECK(settings_read_startup_line(0, verified));
    CHECK(strcmp(verified, "G21") == 0);
}
int main(void)
{
    boot_during_init = seed_custom_records;
    boot_program = "$RST=*\n";
    CHECK(grbl_enter() == 0);
    CHECK(strstr(engine_output, "error:") == NULL);
    CHECK(strstr(engine_output, "[MSG:Restoring defaults]") != NULL);
    nvs_io_t *storage = nvs_buffer_get_physical();
    stored_line_t startup, build_info;
    settings_t saved;
    CHECK(storage->memcpy_from_nvs((uint8_t *)startup, NVS_ADDR_STARTUP_BLOCK, sizeof(startup), true) == NVS_TransferResult_OK);
    CHECK(startup[0] == 0);
    CHECK(storage->memcpy_from_nvs((uint8_t *)build_info, NVS_ADDR_BUILD_INFO, sizeof(build_info), true) == NVS_TransferResult_OK);
    CHECK(strcmp(build_info, BUILD_INFO) == 0);
    CHECK(storage->memcpy_from_nvs((uint8_t *)&saved, NVS_ADDR_GLOBAL, sizeof(saved), true) == NVS_TransferResult_OK);
    NEAR(saved.arc_tolerance, DEFAULT_ARC_TOLERANCE);
    return EXIT_SUCCESS;
}
