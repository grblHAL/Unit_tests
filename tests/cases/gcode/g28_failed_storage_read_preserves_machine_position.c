#include "support/engine_host.h"
#include "check.h"
static bool failed_read(uint8_t *dest, uint32_t source, uint32_t size, bool checksum) { (void)dest; (void)source; (void)size; (void)checksum; return false; }
int main(void)
{
    engine_parser_prepare();
    hal.nvs.memcpy_from_nvs = failed_read;
    char return_home[] = "G28";
    CHECK(gc_execute_block(return_home) == Status_SettingReadFail);
    for(unsigned axis = 0; axis < N_AXIS; axis++) NEAR(gc_state.position[axis], 0);
    return EXIT_SUCCESS;
}
