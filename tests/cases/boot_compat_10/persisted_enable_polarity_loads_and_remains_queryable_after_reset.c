#include "support/boot_legacy_host.h"

static unsigned saved_configuration;
static void persist_enable_policy(void)
{
    char value[] = "0";
    CHECK(settings_store_setting(Setting_InvertStepperEnable, value) == Status_OK);
    settings_t saved;
    CHECK(hal.nvs.memcpy_from_nvs((uint8_t *)&saved, NVS_ADDR_GLOBAL, sizeof(saved), true));
    CHECK(saved.steppers.enable_invert.mask == AXES_BITMASK);
    saved_configuration++;
}
int main(void)
{
    boot_during_init = persist_enable_policy;
    boot_program = "$4\n\x18$4\n";
    run_legacy_boot_program();
    CHECK(saved_configuration == 1 && boot_setup_calls == 1);
    CHECK(settings.steppers.enable_invert.mask == AXES_BITMASK);
    const char *first = strstr(engine_output, "$4=0" ASCII_EOL);
    CHECK(first != NULL);
    CHECK(strstr(first + 1, "$4=0" ASCII_EOL) != NULL);
    CHECK(strstr(engine_output, "error:") == NULL);
    CHECK(!gc_state.modal.units_imperial && !gc_state.modal.distance_incremental);
    return EXIT_SUCCESS;
}
