#include "support/secondary_pwm_settings_host.h"
#include "check.h"

int main(void)
{
    engine_prepare();
    CHECK(hal.nvs.type == NVS_Emulated);
    CHECK(spindle1_settings_add(false) == NULL);
    return EXIT_SUCCESS;
}
