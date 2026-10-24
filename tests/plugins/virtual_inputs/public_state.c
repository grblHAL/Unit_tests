#include "vinput_host.h"
int main(void)
{
    vi_start(true);
    CHECK(virtual_inputs_get().mask == 0);
    CHECK(virtual_input_set(VInput_Probe, true));
    CHECK(virtual_input_get(VInput_Probe));
    CHECK(virtual_inputs_get().mask == 1);
    CHECK(virtual_input_set(VInput_Toolsetter, true));
    CHECK(virtual_inputs_get().mask == 3);
    CHECK(!virtual_input_set(VInput_MaxId, true));
    CHECK(!virtual_input_get(VInput_MaxId));
    virtual_inputs_clear();
    CHECK(virtual_inputs_get().mask == 0);
    return 0;
}
