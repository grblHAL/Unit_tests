#include "support/report_host.h"
#include "protocol.h"

static unsigned return_calls;
static void report_macro_return(void)
{
    CHECK(gc_state.modal.program_flow == ProgramFlow_Return);
    return_calls++;
    engine_output[0] = 0;
    report_gcode_modes(hal.stream.write);
}

int main(void)
{
    prepare_report();
    grbl.on_execute_realtime = protocol_execute_noop;
    grbl.on_macro_return = report_macro_return;
    char block[] = "M99";
    CHECK(gc_execute_block(block) == Status_OK);
    CHECK(return_calls == 1);
    CHECK(strncmp(engine_output, "[GC:", 4) == 0);
    CHECK(strstr(engine_output, " M99") == NULL);
    CHECK(strstr(engine_output, " M5") != NULL);
    CHECK(strstr(engine_output, "]" ASCII_EOL) != NULL);
    CHECK(gc_state.modal.program_flow == ProgramFlow_Running);
    return EXIT_SUCCESS;
}
