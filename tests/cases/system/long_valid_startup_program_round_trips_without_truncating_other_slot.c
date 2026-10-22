#include "support/system_command_host.h"

int main(void)
{
    prepare_system_command();
    CHECK(system_command("$N1=G21") == Status_OK);
    char command[sizeof(stored_line_t) + 8] = "$N0=G90";
    while(strlen(command + 4) + 4 < sizeof(stored_line_t) - 1)
        strcat(command, "|G90");
    stored_line_t expected;
    strcpy(expected, command + 4);
    CHECK(system_execute_line(command, hal.stream.write) == Status_OK);
    stored_line_t saved;
    CHECK(settings_read_startup_line(0, saved));
    CHECK(strcmp(saved, expected) == 0);
    CHECK(settings_read_startup_line(1, saved));
    CHECK(strcmp(saved, "G21") == 0);
    CHECK(!gc_state.modal.distance_incremental);
    CHECK(plan_get_current_block() == NULL);
    return EXIT_SUCCESS;
}
