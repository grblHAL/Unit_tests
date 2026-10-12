#include "support/system_command_host.h"
#include "nvs.h"
#include "check.h"

int main(void)
{
    prepare_system_command();
    stored_line_t empty = "";
    settings_write_startup_line(0, empty);
    settings_write_startup_line(1, empty);
    engine_output[0] = '\0';
    system_execute_startup(NULL);
    CHECK(engine_output[0] == '\0');
    CHECK(!gc_state.modal.units_imperial);
    return EXIT_SUCCESS;
}
