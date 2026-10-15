#include "support/boot_host.h"
#include "nvs_buffer.h"

static bool saw_downgrade;
static void observe_first_command(void)
{
    if(boot_reads == sizeof("$DWNGRD\n") - 1) {
        CHECK(settings.flags.settings_downgrade && settings.version.build == 0);
        saw_downgrade = true;
    }
}
int main(void)
{
    boot_program = "$DWNGRD\n$DWNGRD\n";
    boot_before_read = observe_first_command;
    CHECK(grbl_enter() == 0);
    CHECK(saw_downgrade);
    CHECK(strstr(engine_output, "error:") == NULL);
    CHECK(!settings.flags.settings_downgrade);
    CHECK(settings.version.build == GRBL_BUILD - 20000000UL);
    settings_t saved = {0};
    CHECK(nvs_buffer_get_physical()->memcpy_from_nvs((uint8_t *)&saved, NVS_ADDR_GLOBAL, sizeof(saved), true) == NVS_TransferResult_OK);
    CHECK(!saved.flags.settings_downgrade);
    CHECK(saved.version.build == settings.version.build);
    return EXIT_SUCCESS;
}
