#include "support/settings_file_host.h"
#include "check.h"

int main(void)
{
    prepare_settings_file();
    settings.spindle.ppr = 100;
    hal.driver_cap.spindle_encoder = true;
    grbl.on_file_demarcate(false);
    CHECK(settings.spindle.ppr == 100);
    CHECK(file_callback_calls == 1);
    CHECK(file_callback_start[0] == false);
    return EXIT_SUCCESS;
}
