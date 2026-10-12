#include "support/ioports_settings_host.h"

int main(void)
{
    prepare_io_settings();
    CHECK(store_io_setting(Settings_IoPort_InvertIn, "2") == Status_OK);
    CHECK(store_io_setting(Settings_IoPort_InvertOut, "1") == Status_OK);
    const setting_detail_t *input = setting_get_details(Settings_IoPort_InvertIn, NULL);
    const setting_detail_t *output = setting_get_details(Settings_IoPort_InvertOut, NULL);
    CHECK(input != NULL && output != NULL);
    CHECK(setting_get_int_value(input, 0) == 2);
    CHECK(setting_get_int_value(output, 0) == 1);
    CHECK(settings.ioport.invert_in.mask == 2);
    CHECK(settings.ioport.invert_out.mask == 1);
    return EXIT_SUCCESS;
}
