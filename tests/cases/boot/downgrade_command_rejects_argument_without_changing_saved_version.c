#include "support/boot_host.h"
#include "nvs_buffer.h"

int main(void)
{
    boot_program = "$DWNGRD=1\n";
    CHECK(grbl_enter() == 0);
    CHECK(strstr(engine_output, "error:") != NULL);
    CHECK(!settings.flags.settings_downgrade);
    CHECK(settings.version.build == GRBL_BUILD - 20000000UL);
    settings_t saved = {0};
    CHECK(nvs_buffer_get_physical()->memcpy_from_nvs((uint8_t *)&saved, NVS_ADDR_GLOBAL, sizeof(saved), true) == NVS_TransferResult_OK);
    CHECK(!saved.flags.settings_downgrade);
    CHECK(saved.version.build == settings.version.build);
    return EXIT_SUCCESS;
}
