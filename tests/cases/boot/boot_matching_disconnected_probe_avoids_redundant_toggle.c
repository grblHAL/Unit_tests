#include "support/boot_probe_connection_host.h"

int main(void)
{
    driver_probe_connected = 0;
    boot_control_signals.probe_disconnected = 1;
    boot_during_setup = install_probe_connection;
    CHECK(grbl_enter() == 0);
    CHECK(driver_probe_connected == 0);
    CHECK(driver_probe_toggles == 0);
    return EXIT_SUCCESS;
}
