#include "support/settings_initialized_host.h"
#include "nvs.h"
#include "check.h"

int main(void)
{
    prepare_initialized_settings(2);
    tool_data_t valid = {.tool_id = 4, .radius = 3};
    CHECK(grbl.tool_table.set_tool(&valid));
    tool_data_t invalid = {.tool_id = 5, .radius = 9};
    CHECK(!grbl.tool_table.set_tool(&invalid));
    NEAR(grbl.tool_table.get_tool(4)->data->radius, 3.0f);
    return EXIT_SUCCESS;
}
