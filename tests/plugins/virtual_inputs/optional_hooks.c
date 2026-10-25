#include "vinput_host.h"
int main(void)
{
    vi_start(false);
    CHECK(grbl.on_unknown_realtime_cmd((char)0xB8));
    CHECK(unknown_calls == 0);
    CHECK(virtual_input_set(VInput_Probe, true));
    grbl.on_reset();
    CHECK(resets == 0 && virtual_inputs_get().mask == 0);
    return 0;
}
