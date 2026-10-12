#include "support/settings_host.h"
#include "check.h"

int main(void)
{
    prepare_settings_store();
    settings.parking.flags.value = 7;
    CHECK(store_setting(Setting_ParkingEnable, "6") == Status_OK);
    CHECK(settings.parking.flags.value == 0);
    CHECK(change_callbacks == 1);
    return EXIT_SUCCESS;
}
