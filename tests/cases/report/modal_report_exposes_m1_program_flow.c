#include "support/report_host.h"
#include "protocol.h"
#include "check.h"
static unsigned flow_reports;
static status_code_t report_program_flow(program_flow_t flow, bool check_mode)
{
    CHECK(flow==ProgramFlow_OptionalStop); CHECK(check_mode); flow_reports++;
    engine_output[0]=0; report_gcode_modes(hal.stream.write);
    return Status_Handled;
}
int main(void)
{
    prepare_report(); grbl.on_execute_realtime=protocol_execute_noop;
    grbl.on_program_paused=report_program_flow; char block[]="M1"; CHECK(gc_execute_block(block)==Status_OK);
    CHECK(flow_reports==1); CHECK(strncmp(engine_output,"[GC:",4)==0);
    CHECK(strstr(engine_output," M1 M5")!=NULL); CHECK(strstr(engine_output,"]" ASCII_EOL)!=NULL);
    return EXIT_SUCCESS;
}
