#include "support/can_settings_host.h"

int main(void)
{
    prepare_can_settings();
    CHECK(store_setting(Setting_CANbus_BaudRate, "2") == Status_OK);
    setting_details_t *owner = NULL;
    CHECK(setting_get_details(Setting_CANbus_BaudRate, &owner) != NULL);
    CHECK(owner != NULL);
    canbus_init();
    CHECK(settings.canbus_baud == 2 && can_baud_calls == 1);
    unsigned owners = 0, nodes = 0;
    for(setting_details_t *node = settings_get_details(); node; node = node->next) {
        CHECK(++nodes < 32);
        if(node == owner) owners++;
    }
    CHECK(owners == 1);
    return EXIT_SUCCESS;
}
