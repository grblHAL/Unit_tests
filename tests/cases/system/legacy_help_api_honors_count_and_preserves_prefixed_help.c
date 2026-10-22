#include "support/system_metadata_host.h"
static const sys_command_t commands[] = {
    {.command = "FIXA", .help = {.str = "First"}},
    {.command = "FIXB", .help = {.str = "$FIXB=1 - Second"}},
    {.command = "OMIT", .help = {.str = "Do not list"}}
};
int main(void)
{
    prepare_system_metadata();
    system_output_help(commands, 2);
    CHECK(strcmp(metadata_output, "$FIXA - First." ASCII_EOL "$FIXB=1 - Second." ASCII_EOL) == 0);
    size_t before = strlen(metadata_output);
    system_output_help(commands, 0);
    CHECK(strlen(metadata_output) == before);
    return EXIT_SUCCESS;
}
