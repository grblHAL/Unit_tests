#include "support/probe_connection_setting_host.h"
int main(void)
{
    prepare_probe_connection_setting();
    CHECK(store_disconnection_inversion() == Status_OK);
    CHECK(settings.control_invert.probe_disconnected && probe_connection_toggles == 1);
    CHECK(store_setting(Setting_ControlInvertMask, "0") == Status_OK);
    CHECK(!settings.control_invert.probe_disconnected && probe_connection_toggles == 2);
    return EXIT_SUCCESS;
}
