#include "support/settings_initialized_host.h"
#include "nvs.h"
#include "check.h"

int main(void)
{
    prepare_initialized_settings(2);
    tool_data_t written = {.tool_id = 1, .radius = 3};
    CHECK(host_save_tool(&written));
    tool_data_t current = {.tool_id = 0, .radius = 9};
    CHECK(host_save_tool(&current));
    NEAR(grbl.tool_table.get_tool(1)->data->radius, 3.0f);
    CHECK(grbl.tool_table.get_tool(0)->pocket == 0);
    return EXIT_SUCCESS;
}
