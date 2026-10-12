#include "support/ioports_settings_host.h"
#include "check.h"

int main(void)
{
    prepare_io_settings();
    CHECK(store_io_setting(Settings_IoPort_OD_Enable, "2") == Status_SettingDisabled);
    CHECK(output_config_calls[0] == 0 && output_config_calls[1] == 0);
    CHECK(settings.ioport.od_enable_out.mask == 0);
    return EXIT_SUCCESS;
}
