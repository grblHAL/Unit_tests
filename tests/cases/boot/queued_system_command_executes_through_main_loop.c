#include "support/boot_host.h"
#include "check.h"
static void enqueue_modal_report(void)
{
    char command[] = "$G";
    CHECK(protocol_enqueue_gcode(command));
}

int main(void)
{
    boot_program = "";
    boot_before_read = enqueue_modal_report;
    CHECK(grbl_enter() == 0);
    CHECK(strstr(engine_output, "[GC:G0 G54 G17 G21 G90") != NULL);
    return EXIT_SUCCESS;
}
