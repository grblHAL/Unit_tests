#include "support/settings_initialized_host.h"
#include "nvs.h"
#include "check.h"

int main(void)
{
    prepare_initialized_settings(2);
    tool_table_entry_t *entry = grbl.tool_table.get_tool(5);
    CHECK(entry->data == NULL);
    CHECK(entry->pocket == (pocket_id_t)-1);
    return EXIT_SUCCESS;
}
