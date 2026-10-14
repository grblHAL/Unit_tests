#include "support/boot_toolsetter_callbacks_host.h"

int main(void)
{
    prepare_boot_toolsetter();
    probe_selection_ok = false;
    tool_data_t tool = {0}; coord_data_t position = {0};
    CHECK(!grbl.on_probe_toolsetter(&tool, &position, true, true));
    CHECK(probe_select_calls == 1 && selected_probe == Probe_Toolsetter);
    return EXIT_SUCCESS;
}
