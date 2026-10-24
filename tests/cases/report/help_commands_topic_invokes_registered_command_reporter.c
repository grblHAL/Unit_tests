#include "support/report_host.h"
static unsigned calls;
static void commands(void) { calls++; hal.stream.write("Custom command help" ASCII_EOL); }
int main(void)
{
    prepare_report();
    for(unsigned pass = 0; pass < 3; pass++) {
        bool installed = pass != 1;
        grbl.on_report_command_help = installed ? commands : NULL;
        engine_output[0] = 0;
        char topic[] = "commands";
        CHECK(report_help(topic) == Status_OK);
        CHECK(calls == (pass == 2 ? 2u : 1u));
        CHECK(strcmp(engine_output, installed ? "Custom command help" ASCII_EOL : "") == 0);
    }
    return EXIT_SUCCESS;
}
