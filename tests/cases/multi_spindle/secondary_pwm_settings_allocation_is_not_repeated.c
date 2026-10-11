#include "support/secondary_pwm_settings_host.h"
#include "check.h"

int main(void)
{
    prepare_secondary_pwm_settings(false);
    uint32_t allocated_size = hal.nvs.driver_area.size;
    CHECK(spindle1_settings_add(false) == NULL);
    CHECK(hal.nvs.driver_area.size == allocated_size);
    nvs_buffer_free();
    return EXIT_SUCCESS;
}
