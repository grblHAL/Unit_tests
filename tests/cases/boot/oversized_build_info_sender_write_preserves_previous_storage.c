#include "support/boot_host.h"
#include "nvs_buffer.h"
static void store_previous_info(void)
{
    CHECK(settings_write_build_info("Previous machine"));
}
int main(void)
{
    char program[sizeof(stored_line_t) + 16] = "$I=";
    memset(program + 3, 'X', sizeof(stored_line_t) - 1);
    strcpy(program + 3 + sizeof(stored_line_t) - 1, "\n$I\n");
    boot_during_init = store_previous_info;
    boot_program = program;
    CHECK(grbl_enter() == 0);
    CHECK(strstr(engine_output, "error:3") != NULL);
    CHECK(strstr(engine_output, "Previous machine") != NULL);
    stored_line_t saved = {0};
    CHECK(nvs_buffer_get_physical()->memcpy_from_nvs((uint8_t *)saved, NVS_ADDR_BUILD_INFO, sizeof(saved), true) == NVS_TransferResult_OK);
    CHECK(strcmp(saved, "Previous machine") == 0);
    return EXIT_SUCCESS;
}
