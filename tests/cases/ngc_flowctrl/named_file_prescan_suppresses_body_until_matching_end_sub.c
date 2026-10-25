#define NAMED_MACRO_BODY "#100=[#100+1]\n(MSG,Executed once)\n"
#include "support/embedded_macro_protocol_host.h"
static unsigned scan_polls;
static void observe_named_scan(sys_state_t state)
{
    (void)state;
    if(hal.stream.file && hal.stream.file != ram_macro_files[0] && gc_state.skip_blocks) {
        scan_polls++;
        NEAR(ram_flow_parameter(100), 0);
        CHECK(strstr(engine_output, "Executed once") == NULL);
    }
}
static void install_scan_observer(void)
{
    register_named_macro_assets();
    grbl.on_execute_realtime = observe_named_scan;
}
int main(void)
{
    ram_prepare_assets = install_scan_observer;
    run_ram_root_protocol("#100=0\nO<fixture>CALL\n#101=7\n");
    CHECK(scan_polls > 0);
    NEAR(ram_flow_parameter(100), 1);
    NEAR(ram_flow_parameter(101), 7);
    char *message = strstr(engine_output, "Executed once");
    CHECK(message != NULL && strstr(message + 1, "Executed once") == NULL);
    return EXIT_SUCCESS;
}
