#include "support/ioports_settings_host.h"

int main(void)
{
    prepare_io_settings();
    CHECK(store_io_setting(Settings_IoPort_Pullup_Disable, "3") == Status_OK);
    const setting_detail_t *detail = setting_get_details(Settings_IoPort_Pullup_Disable, NULL);
    CHECK(detail != NULL);
    CHECK(setting_get_int_value(detail, 0) == 3);
    CHECK(settings.ioport.invert_in.mask == 0 && settings.ioport.invert_out.mask == 0);
    return EXIT_SUCCESS;
}
