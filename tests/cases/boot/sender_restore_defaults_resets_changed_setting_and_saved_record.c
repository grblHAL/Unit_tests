#include "support/boot_host.h"
#include "nvs_buffer.h"
static bool saw_custom_setting;
static void observe_setting_before_restore(void)
{
    if(boot_reads == sizeof("$12=0.1\n") - 1) {
        NEAR(settings.arc_tolerance, 0.1f);
        saw_custom_setting = true;
    }
}
int main(void)
{
    boot_program = "$12=0.1\n$RST=$\n";
    boot_before_read = observe_setting_before_restore;
    CHECK(grbl_enter() == 0);
    CHECK(saw_custom_setting && strstr(engine_output, "error:") == NULL);
    NEAR(settings.arc_tolerance, DEFAULT_ARC_TOLERANCE);
    settings_t saved;
    CHECK(nvs_buffer_get_physical()->memcpy_from_nvs((uint8_t *)&saved, NVS_ADDR_GLOBAL, sizeof(saved), true) == NVS_TransferResult_OK);
    NEAR(saved.arc_tolerance, DEFAULT_ARC_TOLERANCE);
    return EXIT_SUCCESS;
}
