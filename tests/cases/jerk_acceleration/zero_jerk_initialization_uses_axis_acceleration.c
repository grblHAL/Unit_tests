#include "support/settings_initialized_host.h"
#include "check.h"

int main(void)
{
    prepare_settings_store(); hal.step_us_min=2;
    settings.axis[X_AXIS].acceleration=100; settings.axis[X_AXIS].jerk=0;
    settings.axis[Y_AXIS].jerk=123000;
    settings.version.id=SETTINGS_VERSION; hal.nvs.put_byte(0,SETTINGS_VERSION); settings_write_global(); settings_init();
    NEAR(settings.axis[X_AXIS].jerk,60000); NEAR(settings.axis[Y_AXIS].jerk,123000);
    return EXIT_SUCCESS;
}
