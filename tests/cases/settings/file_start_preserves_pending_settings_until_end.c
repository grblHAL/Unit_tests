#include "support/settings_file_host.h"
#include "check.h"

int main(void)
{
    prepare_settings_file();
    settings.planner_buffer_blocks = 29;
    grbl.on_file_demarcate(true);
    CHECK(settings.planner_buffer_blocks == 29);
    CHECK(file_callback_calls == 1);
    CHECK(file_callback_start[0] == true);
    return EXIT_SUCCESS;
}
