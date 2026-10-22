#include "support/system_metadata_host.h"

static status_code_t accessory_command(sys_state_t state, char *args)
{
    (void)state; (void)args;
    CHECK(false);
    return Status_Unhandled;
}

int main(void)
{
    prepare_system_metadata();
    static const sys_command_t vacuum[] = {
        {.command = "VACUUM", .execute = accessory_command, .help = {.str = "control dust extraction"}}
    };
    static const sys_command_t light[] = {
        {.command = "LIGHT", .execute = accessory_command, .help = {.str = "control work light"}}
    };
    static sys_commands_t first = {.n_commands = 1, .commands = vacuum};
    static sys_commands_t second = {.n_commands = 1, .commands = light};
    system_register_commands(&first);
    system_register_commands(&second);
    CHECK(system_command("$HELP COMMANDS") == Status_OK);
    const char *vacuum_help = strstr(metadata_output, "$VACUUM - control dust extraction.");
    const char *light_help = strstr(metadata_output, "$LIGHT - control work light.");
    CHECK(vacuum_help && light_help);
    CHECK(strstr(vacuum_help + 1, "$VACUUM -") == NULL);
    CHECK(strstr(light_help + 1, "$LIGHT -") == NULL);
    const char *parser_help = strstr(metadata_output, "$G - output parser state.");
    CHECK(parser_help && strstr(parser_help + 1, "$G - output parser state.") == NULL);
    return EXIT_SUCCESS;
}
