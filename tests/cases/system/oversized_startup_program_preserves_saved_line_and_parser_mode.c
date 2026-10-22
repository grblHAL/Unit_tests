#include "support/system_command_host.h"

int main(void)
{
    prepare_system_command();
    CHECK(system_command("$N0=G91") == Status_OK);
    CHECK(gc_state.modal.distance_incremental);
    char command[sizeof(stored_line_t) + 12] = "$N0=";
    while(strlen(command + 4) < sizeof(stored_line_t) - 1)
        strcat(command, strlen(command) == 4 ? "G90" : "|G90");
    CHECK(system_execute_line(command, hal.stream.write) == Status_Overflow);
    stored_line_t saved;
    CHECK(settings_read_startup_line(0, saved));
    CHECK(strcmp(saved, "G91") == 0);
    CHECK(gc_state.modal.distance_incremental);
    CHECK(plan_get_current_block() == NULL);
    return EXIT_SUCCESS;
}
