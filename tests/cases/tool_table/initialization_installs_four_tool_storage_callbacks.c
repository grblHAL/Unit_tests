#include "support/settings_initialized_host.h"
#include "nvs.h"
#include "check.h"

int main(void)
{
    prepare_initialized_settings(2);
    CHECK(grbl.tool_table.n_tools == 4);
    CHECK(grbl.tool_table.get_tool != NULL);
    CHECK(grbl.tool_table.set_tool != NULL);
    CHECK(grbl.tool_table.clear != NULL);
    return EXIT_SUCCESS;
}
