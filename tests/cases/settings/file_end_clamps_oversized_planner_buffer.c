#include "support/settings_file_host.h"
#include "check.h"

int main(void)
{
    prepare_settings_file();
    settings.planner_buffer_blocks = 1001;
    grbl.on_file_demarcate(false);
    CHECK(settings.planner_buffer_blocks == 35);
    CHECK(file_callback_calls == 1);
    CHECK(file_callback_start[0] == false);
    return EXIT_SUCCESS;
}
