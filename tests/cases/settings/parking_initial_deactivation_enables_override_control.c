#include "support/settings_host.h"
#include "check.h"

int main(void)
{
    prepare_settings_store();
    CHECK(store_setting(Setting_ParkingEnable, "3") == Status_OK);
    CHECK(settings.parking.flags.enabled);
    CHECK(settings.parking.flags.deactivate_upon_init);
    CHECK(settings.parking.flags.enable_override_control);
    CHECK(change_callbacks == 1);
    return EXIT_SUCCESS;
}
