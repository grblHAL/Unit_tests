#include "support/builtin_macro_host.h"
int main(void)
{
    prepare_settings_store();
    CHECK(builtin_macro_block("G65P1Q10S3") == Status_OK);
    CHECK(settings.status_report.mask == 3 && change_callbacks == 1);
    NEAR(builtin_macro_result("_value"), 3);
    NEAR(builtin_macro_result("_value_returned"), 1);
    CHECK(builtin_macro_block("G65P1Q10S32768") == Status_SettingValueOutOfRange);
    CHECK(settings.status_report.mask == 3 && change_callbacks == 1);
    settings_t saved;
    CHECK(hal.nvs.memcpy_from_nvs((uint8_t *)&saved, NVS_ADDR_GLOBAL,
        sizeof(saved), true) == NVS_TransferResult_OK);
    CHECK(saved.status_report.mask == 3);
    CHECK(builtin_macro_block("G65P1Q10") == Status_OK);
    NEAR(builtin_macro_result("_value"), 3);
    CHECK(builtin_macro_block("G65P1Q10S1") == Status_OK);
    CHECK(settings.status_report.mask == 1 && change_callbacks == 2);
    NEAR(builtin_macro_result("_value"), 1);
    NEAR(builtin_macro_result("_value_returned"), 1);
    CHECK(hal.nvs.memcpy_from_nvs((uint8_t *)&saved, NVS_ADDR_GLOBAL,
        sizeof(saved), true) == NVS_TransferResult_OK);
    CHECK(saved.status_report.mask == 1);
    NEAR(gc_state.modal.spindle[0].rpm, 0);
    return EXIT_SUCCESS;
}
