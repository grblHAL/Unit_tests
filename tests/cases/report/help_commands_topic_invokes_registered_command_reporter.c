#include "support/report_host.h"
static unsigned calls;
static void commands(void) { calls++; hal.stream.write("Custom command help" ASCII_EOL); }
int main(void)
{
    prepare_report();
    grbl.on_report_command_help = commands;
    char topic[] = "commands";
    CHECK(report_help(topic) == Status_OK);
    CHECK(calls == 1);
    CHECK(strcmp(engine_output, "Custom command help" ASCII_EOL) == 0);
    return EXIT_SUCCESS;
}
