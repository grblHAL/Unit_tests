#include "support/settings_file_host.h"
#include "check.h"

int main(void)
{
    prepare_settings_file();
    settings.mode = Mode_Laser;
    grbl.on_file_demarcate(false);
    CHECK(settings.mode == Mode_Standard);
    CHECK(file_callback_calls == 1);
    CHECK(file_callback_start[0] == false);
    return EXIT_SUCCESS;
}
