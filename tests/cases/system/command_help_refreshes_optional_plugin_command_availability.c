#include "support/system_metadata_host.h"

static status_code_t accessory_command(sys_state_t state, char *args)
{
    (void)state; (void)args;
    CHECK(false);
    return Status_Unhandled;
}

static bool accessory_available;
static unsigned help_calls;
static const char *accessory_help(const char *command)
{
    CHECK(strcmp(command, "LIGHT") == 0);
    help_calls++;
    return accessory_available ? "control work light" : NULL;
}

int main(void)
{
    prepare_system_metadata();
    static const sys_command_t commands[] = {
        {.command = "LIGHT", .execute = accessory_command, .flags = {.help_fn = true}, .help = {.fn = accessory_help}}
    };
    static sys_commands_t plugin = {.n_commands = 1, .commands = commands};
    system_register_commands(&plugin);
    CHECK(system_command("$HELP COMMANDS") == Status_OK);
    CHECK(strstr(metadata_output, "$LIGHT -") == NULL);
    CHECK(help_calls == 1);
    accessory_available = true;
    metadata_output[0] = '\0';
    CHECK(system_command("$HELP COMMANDS") == Status_OK);
    CHECK(strstr(metadata_output, "$LIGHT - control work light.") != NULL);
    CHECK(help_calls == 2);
    return EXIT_SUCCESS;
}
