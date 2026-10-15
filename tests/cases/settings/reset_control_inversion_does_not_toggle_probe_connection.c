#include "support/probe_connection_setting_host.h"
int main(void)
{
    prepare_probe_connection_setting();
    CHECK(store_setting(Setting_ControlInvertMask, "1") == Status_OK);
    CHECK(settings.control_invert.reset && !settings.control_invert.probe_disconnected);
    CHECK(probe_connection_toggles == 0);
    return EXIT_SUCCESS;
}
