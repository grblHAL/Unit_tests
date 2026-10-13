#include "support/settings_initialized_host.h"

int main(void)
{
    prepare_initialized_settings(2);
    tool_data_t stored = {.tool_id = 2, .radius = 2.5f, .offset.values = {1, 2, 3}};
    CHECK(host_save_tool(&stored));
    settings.flags.tool_persistent = true;
    settings.tool_id = 2;
    sys.cold_start = true;
    gc_init(false);
    CHECK(gc_state.tool->tool_id == 2);
    NEAR(gc_state.tool->radius, 2.5f);
    for(unsigned i = 0; i < 3; i++) NEAR(gc_state.tool->offset.values[i], (float)(i + 1));
    return EXIT_SUCCESS;
}
