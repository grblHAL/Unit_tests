#include "support/m98_prescan_host.h"
#include "support/system_command_host.h"
#include "check.h"
static unsigned completion_calls;
static void completed(program_flow_t flow, bool check_mode)
{
    CHECK(flow == ProgramFlow_Return && check_mode);
    completion_calls++;
}
int main(void)
{
    prepare_m98_prescan();
    grbl.on_execute_realtime = protocol_execute_noop;
    hal.control.get_state = command_control_state;
    grbl.on_program_completed = completed;
    CHECK(macro_block("M99") == Status_OK);
    CHECK(completion_calls == 1);
    CHECK(gc_state.modal.program_flow == ProgramFlow_Running);
    close_flow_file();
    return EXIT_SUCCESS;
}
