#include "support/settings_initialized_host.h"
#include "nvs.h"
#include "check.h"

int main(void)
{
    prepare_initialized_settings(2);
    tool_data_t written = {.tool_id = 2, .offset.values = {1.25f, 2.5f, 3.75f}, .radius = 4.5f};
    CHECK(host_save_tool(&written));
    tool_table_entry_t *entry = grbl.tool_table.get_tool(2);
    CHECK(entry->data != NULL);
    CHECK(entry->data->tool_id == 2);
    CHECK(entry->pocket == 2);
    NEAR(entry->data->offset.values[0], 1.25f);
    NEAR(entry->data->offset.values[1], 2.5f);
    NEAR(entry->data->offset.values[2], 3.75f);
    NEAR(entry->data->radius, 4.5f);
    return EXIT_SUCCESS;
}
