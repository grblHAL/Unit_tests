#include "vinput_host.h"
int main(void)
{
    vi_start(true);
    probe_get_state_ptr state = hal.probe.get_state;
    on_unknown_realtime_cmd_ptr rt = grbl.on_unknown_realtime_cmd;
    virtual_inputs_init();
    CHECK(hal.probe.get_state == state && grbl.on_unknown_realtime_cmd == rt && registrations == 1);
    CHECK(virtual_input_set(VInput_Probe, true));
    CHECK(hal.probe.get_state().triggered);
    return 0;
}
