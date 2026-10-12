#include "support/system_command_host.h"
#include "nvs.h"
#include "check.h"

int main(void)
{
    prepare_system_command();
    stored_line_t first = "G20|G91|G55", second = "G21";
    settings_write_startup_line(0, first);
    settings_write_startup_line(1, second);
    engine_output[0] = '\0';
    hal.nvs.type = NVS_None;
    sys.flags.single_block = true;
    system_execute_startup(NULL);
    CHECK(sys.flags.single_block);
    CHECK(!gc_state.modal.units_imperial);
    CHECK(!gc_state.modal.distance_incremental);
    CHECK(engine_output[0] == '\0');
    return EXIT_SUCCESS;
}
