#include "support/settings_initialized_host.h"
#include "nvs.h"
#include "check.h"

int main(void)
{
    prepare_initialized_settings(2);
    tool_data_t written = {.tool_id = 4, .radius = 2.25f};
    CHECK(host_save_tool(&written));
    tool_table_entry_t *entry = grbl.tool_table.get_tool(4);
    CHECK(entry->data && entry->data->tool_id == 4);
    NEAR(entry->data->radius, 2.25f);
    return EXIT_SUCCESS;
}
