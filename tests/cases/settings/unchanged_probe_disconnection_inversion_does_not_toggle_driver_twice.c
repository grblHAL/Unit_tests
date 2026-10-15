#include "support/probe_connection_setting_host.h"
int main(void)
{
    prepare_probe_connection_setting();
    CHECK(store_disconnection_inversion() == Status_OK);
    CHECK(store_disconnection_inversion() == Status_OK);
    CHECK(settings.control_invert.probe_disconnected && probe_connection_toggles == 1);
    return EXIT_SUCCESS;
}
