#include "support/secondary_pwm_settings_host.h"
#include "check.h"

int main(void)
{
    prepare_secondary_pwm_settings(false);
    grbl.on_settings_changed(&settings, (settings_changed_flags_t){0});
    CHECK(primary_pwm_changes == 1 && secondary_pwm_changes == 0);
    nvs_buffer_free();
    return EXIT_SUCCESS;
}
