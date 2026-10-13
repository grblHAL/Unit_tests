#include "support/can_settings_host.h"

int main(void)
{
    prepare_can_settings();
    settings.canbus_baud = 3;
    setting_details_t *owner = NULL;
    CHECK(setting_get_details(Setting_CANbus_BaudRate, &owner) != NULL);
    CHECK(owner && owner->restore);
    owner->restore();
    CHECK(settings.canbus_baud == 0);
    CHECK(can_baud_calls == 0);
    return EXIT_SUCCESS;
}
