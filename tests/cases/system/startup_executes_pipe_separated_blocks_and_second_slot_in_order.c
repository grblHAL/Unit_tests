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
    system_execute_startup(NULL);
    CHECK(!gc_state.modal.units_imperial);
    CHECK(gc_state.modal.distance_incremental);
    CHECK(gc_state.modal.g5x_offset.id == CoordinateSystem_G55);
    CHECK(strcmp(engine_output, ">G20:ok" ASCII_EOL ">G91:ok" ASCII_EOL ">G55:ok" ASCII_EOL ">G21:ok" ASCII_EOL) == 0);
    return EXIT_SUCCESS;
}
