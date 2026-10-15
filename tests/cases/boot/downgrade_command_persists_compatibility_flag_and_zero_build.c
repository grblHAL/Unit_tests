#include "support/boot_host.h"
#include "nvs_buffer.h"

int main(void)
{
    boot_program = "$DWNGRD\n";
    CHECK(grbl_enter() == 0);
    CHECK(strstr(engine_output, "error:") == NULL);
    CHECK(settings.flags.settings_downgrade);
    CHECK(settings.version.build == 0);
    settings_t saved = {0};
    CHECK(nvs_buffer_get_physical()->memcpy_from_nvs((uint8_t *)&saved, NVS_ADDR_GLOBAL, sizeof(saved), true) == NVS_TransferResult_OK);
    CHECK(saved.flags.settings_downgrade && saved.version.build == 0);
    return EXIT_SUCCESS;
}
