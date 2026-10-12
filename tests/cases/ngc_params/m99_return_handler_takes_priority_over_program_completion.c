#include "support/m98_prescan_host.h"
#include "support/system_command_host.h"
#include "check.h"
static unsigned return_calls, completion_calls;
static void returned(void) { return_calls++; }
static void completed(program_flow_t flow, bool check_mode)
{
    (void)flow;
    (void)check_mode;
    completion_calls++;
}
int main(void)
{
    prepare_m98_prescan();
    grbl.on_execute_realtime = protocol_execute_noop;
    hal.control.get_state = command_control_state;
    grbl.on_program_completed = completed;
    grbl.on_macro_return = returned;
    CHECK(macro_block("M99") == Status_OK);
    CHECK(return_calls == 1 && completion_calls == 0);
    close_flow_file();
    return EXIT_SUCCESS;
}
