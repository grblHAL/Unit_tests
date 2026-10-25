#include "vinput_host.h"
int main(void)
{
    vi_start(true);
    CHECK(grbl.on_unknown_realtime_cmd((char)CMD_VINPUT_PROBE_SET));
    CHECK(virtual_input_set(VInput_Toolsetter, true));
    vi_configure(false, true);
    vi_configure(false, false);
    CHECK(virtual_inputs_get().mask == 3);
    grbl.on_reset();
    CHECK(resets == 1 && virtual_inputs_get().mask == 0);
    CHECK(vi_command(NULL) == Status_OK);
    CHECK(strstr(output, "PROBE_SET=1"));
    return 0;
}
