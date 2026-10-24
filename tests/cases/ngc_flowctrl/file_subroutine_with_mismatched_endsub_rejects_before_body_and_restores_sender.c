#include "support/ram_macro_protocol_host.h"
static status_code_t observe_mismatched_end(vfs_file_t *file, status_code_t status)
{
    (void)file;
    fprintf(stderr, "Mismatched ENDSUB: status=%u body=%.0f tail=%.0f\n",
        (unsigned)status, ram_flow_parameter(100), ram_flow_parameter(101));
    return status;
}
static void observe_file_end(void) { grbl.on_file_end = observe_mismatched_end; }
int main(void)
{
    ram_prepare_assets = observe_file_end;
    ram_expected_root_status = Status_FlowControlSyntaxError;
    run_ram_root_protocol("#1=99\n#100=0\n#101=0\nO10SUB\n#100=88\n"
        "O20ENDSUB\n#101=7\n");
    NEAR(ram_flow_parameter(1), 99);
    NEAR(ram_flow_parameter(100), 0);
    NEAR(ram_flow_parameter(101), 0);
    CHECK(gc_state.last_error == Status_OK);
    CHECK(state_get() == STATE_IDLE && plan_get_current_block() == NULL);
    CHECK(sys.alarm == Alarm_None); // The helper ends the host through CMD_EXIT.
    return EXIT_SUCCESS;
}
