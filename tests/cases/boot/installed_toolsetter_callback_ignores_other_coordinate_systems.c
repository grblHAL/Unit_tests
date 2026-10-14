#include "support/boot_toolsetter_callbacks_host.h"

int main(void)
{
    prepare_boot_toolsetter();
    tool_data_t tool = {0}; coord_data_t position = {0};
    CHECK(!grbl.on_probe_toolsetter(&tool, &position, false, true));
    CHECK(!grbl.on_probe_toolsetter(&tool, &position, false, false));
    CHECK(probe_select_calls == 0);
    return EXIT_SUCCESS;
}
