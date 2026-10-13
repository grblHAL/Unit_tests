#include "support/settings_initialized_host.h"
#include "nvs.h"
#include "check.h"

int main(void)
{
    prepare_initialized_settings(2);
    tool_data_t written = {.tool_id = 2, .radius = 3.5f};
    CHECK(host_save_tool(&written));
    tool_table_entry_t *entry = grbl.tool_table.get_tool_by_idx(2);
    CHECK(entry->data && entry->data->tool_id == 2);
    CHECK(entry->pocket == 2);
    NEAR(entry->data->radius, 3.5f);
    return EXIT_SUCCESS;
}
