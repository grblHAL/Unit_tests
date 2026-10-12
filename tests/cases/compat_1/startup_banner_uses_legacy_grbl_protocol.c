#include "support/report_host.h"
#include "check.h"

int main(void)
{
    prepare_report();
    grbl.report.init_message(hal.stream.write);
    CHECK(strcmp(engine_output, ASCII_EOL "Grbl " GRBL_VERSION " ['$' for help]" ASCII_EOL) == 0);
    return EXIT_SUCCESS;
}
