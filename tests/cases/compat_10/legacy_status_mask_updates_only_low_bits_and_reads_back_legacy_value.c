#include "support/settings_initialized_host.h"
int main(void)
{
    prepare_initialized_settings(2);
    settings.status_report.mask = 0x125;
    CHECK(store_setting(Setting_StatusReportMask, "2") == Status_OK);
    CHECK(settings.status_report.mask == 0x126);
    const setting_detail_t *detail = setting_get_details(Setting_StatusReportMask, NULL);
    CHECK(detail != NULL && setting_get_int_value(detail, 0) == 2);
    settings_t saved;
    CHECK(hal.nvs.memcpy_from_nvs((uint8_t *)&saved, NVS_ADDR_GLOBAL, sizeof(saved), true) == NVS_TransferResult_OK);
    CHECK(saved.status_report.mask == 0x126);
    return EXIT_SUCCESS;
}
