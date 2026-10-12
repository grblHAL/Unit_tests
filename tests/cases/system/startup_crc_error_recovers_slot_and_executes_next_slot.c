#include "support/system_command_host.h"
#include "nvs.h"
#include "check.h"

int main(void)
{
    prepare_system_command();
    stored_line_t first = "G20", second = "G91", recovered;
    settings_write_startup_line(0, first);
    settings_write_startup_line(1, second);
    hal.nvs.put_byte(NVS_ADDR_STARTUP_BLOCK, hal.nvs.get_byte(NVS_ADDR_STARTUP_BLOCK) ^ 1);
    engine_output[0] = '\0';
    sys.flags.single_block = true;
    system_execute_startup(NULL);
    CHECK(strcmp(engine_output, ">:error:7" ASCII_EOL ">G91:ok" ASCII_EOL) == 0);
    CHECK(!gc_state.modal.units_imperial);
    CHECK(gc_state.modal.distance_incremental);
    CHECK(sys.flags.single_block);
    CHECK(settings_read_startup_line(0, recovered));
    CHECK(recovered[0] == '\0');
    return EXIT_SUCCESS;
}
