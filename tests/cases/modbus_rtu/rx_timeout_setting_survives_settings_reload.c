#include "support/rtu_host.h"

int main(void)
{
    prepare_rtu();
    setting_details_t *owner = NULL;
    const setting_detail_t *detail = setting_get_details(Settings_ModBus_RXTimeout, &owner);
    CHECK(detail != NULL && owner != NULL && owner->load != NULL);
    char timeout[] = "125";
    CHECK(settings_store_setting(Settings_ModBus_RXTimeout, timeout) == Status_OK);
    CHECK(setting_get_int_value(detail, 0) == 125);
    owner->load();
    CHECK(setting_get_int_value(detail, 0) == 125);
    return EXIT_SUCCESS;
}
