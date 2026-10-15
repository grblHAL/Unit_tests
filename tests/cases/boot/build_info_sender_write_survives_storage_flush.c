#include "support/boot_host.h"
#include "nvs_buffer.h"
int main(void)
{
    boot_program = "$I=Workshop router\n$I\n";
    CHECK(grbl_enter() == 0);
    CHECK(strstr(engine_output, "error:") == NULL);
    CHECK(strstr(engine_output, "Workshop router") != NULL);
    stored_line_t saved = {0};
    CHECK(nvs_buffer_get_physical()->memcpy_from_nvs((uint8_t *)saved, NVS_ADDR_BUILD_INFO, sizeof(saved), true) == NVS_TransferResult_OK);
    CHECK(strcmp(saved, "Workshop router") == 0);
    return EXIT_SUCCESS;
}
