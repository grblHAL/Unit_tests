#include "seal_host.h"
int main(void)
{
    seal_start();
    CHECK(registered_settings->settings[0].id == 450 &&
          registered_settings->settings[0].flags.reboot_required);
    CHECK(seal_read_port() == 1 && claims == 1);
    CHECK(seal_port(2) == Status_AuxiliaryPortUnavailable && seal_read_port() == 1);
    CHECK(seal_port(0) == Status_OK && seal_read_port() == 0);
    CHECK(seal_port(-1) == Status_OK && seal_read_port() == -1);
    registered_settings->save();
    registered_settings->load();
    CHECK(seal_read_port() == -1 && claims == 1);
    seal_state(STATE_CYCLE);
    CHECK(solenoid && output_port == 0 && outputs == 1);
    seal_state(STATE_IDLE);
    seal_expire();
    CHECK(!solenoid && output_port == 0 && outputs == 2 && claims == 1);
    return 0;
}
