#include "support/settings_file_host.h"
#include "check.h"

int main(void)
{
    prepare_settings_file();
    settings.probe.probe2_auto_select = true;
    hal.driver_cap.probe2 = false;
    grbl.on_file_demarcate(false);
    CHECK(!settings.probe.probe2_auto_select);
    CHECK(file_callback_calls == 1);
    CHECK(file_callback_start[0] == false);
    return EXIT_SUCCESS;
}
