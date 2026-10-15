#include "support/boot_host.h"
#include "nvs_buffer.h"
int main(void)
{
    boot_program = "$I=RouterX\177\n$I\n";
    CHECK(grbl_enter() == 0);
    CHECK(strstr(engine_output, "error:") == NULL);
    CHECK(strstr(engine_output, "RouterX") == NULL);
    CHECK(strstr(engine_output, "Router") != NULL);
    stored_line_t saved;
    CHECK(nvs_buffer_get_physical()->memcpy_from_nvs((uint8_t *)saved, NVS_ADDR_BUILD_INFO, sizeof(saved), true) == NVS_TransferResult_OK);
    CHECK(strcmp(saved, "Router") == 0);
    return EXIT_SUCCESS;
}
