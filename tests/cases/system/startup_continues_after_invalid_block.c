#include "support/system_command_host.h"
#include "nvs.h"
#include "check.h"

int main(void)
{
    prepare_system_command();
    stored_line_t first = "G999|G20", second = "G91";
    settings_write_startup_line(0, first);
    settings_write_startup_line(1, second);
    engine_output[0] = '\0';
    system_execute_startup(NULL);
    CHECK(gc_state.modal.units_imperial);
    CHECK(gc_state.modal.distance_incremental);
    CHECK(strstr(engine_output, ">G999:error:20" ASCII_EOL ">G20:ok" ASCII_EOL ">G91:ok" ASCII_EOL) != NULL);
    return EXIT_SUCCESS;
}
