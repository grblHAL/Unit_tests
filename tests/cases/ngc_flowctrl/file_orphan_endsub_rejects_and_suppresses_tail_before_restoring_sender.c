#include "support/ram_macro_protocol_host.h"
int main(void)
{
    ram_expected_root_status = Status_FlowControlSyntaxError;
    run_ram_root_protocol("#1=99\n#100=0\nO20ENDSUB\n#100=7\n");
    NEAR(ram_flow_parameter(1), 99);
    NEAR(ram_flow_parameter(100), 0);
    CHECK(gc_state.last_error == Status_OK);
    CHECK(state_get() == STATE_IDLE && plan_get_current_block() == NULL);
    CHECK(sys.alarm == Alarm_None); // The helper ends the host through CMD_EXIT.
    return EXIT_SUCCESS;
}
