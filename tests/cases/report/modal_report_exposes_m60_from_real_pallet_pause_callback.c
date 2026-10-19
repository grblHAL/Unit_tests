#include "support/program_end_host.h"
static unsigned pallet_flow_reports;
static status_code_t report_pallet_pause(program_flow_t flow, bool check_mode)
{
    CHECK(flow == ProgramFlow_CompletedM60 && !check_mode);
    pallet_flow_reports++;
    report_gcode_modes(hal.stream.write);
    return Status_Handled;
}
int main(void)
{
    prepare_program_end(false);
    grbl.on_program_paused = report_pallet_pause;
    CHECK(program_block("M60") == Status_OK);
    CHECK(pallet_flow_reports == 1 && program_pallet_calls == 1);
    CHECK(program_complete_calls == 0);
    CHECK(strstr(engine_output, " M60 M5") != NULL);
    return EXIT_SUCCESS;
}
