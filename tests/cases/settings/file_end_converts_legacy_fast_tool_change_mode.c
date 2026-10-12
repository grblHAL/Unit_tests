#include "support/settings_file_host.h"
#include "check.h"

int main(void)
{
    prepare_settings_file();
    settings.tool_change.mode = (toolchange_mode_t)5;
    grbl.on_file_demarcate(false);
    CHECK(settings.tool_change.mode == ToolChange_SemiAutomatic);
    CHECK(settings.flags.tool_change_fast_pulloff);
    CHECK(file_callback_calls == 1);
    CHECK(file_callback_start[0] == false);
    return EXIT_SUCCESS;
}
