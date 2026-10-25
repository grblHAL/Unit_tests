#include "interlock_host.h"
int main(void)
{
    input_count = output_count = 0;
    il_start();
    CHECK(registered_settings->n_settings == 16);
    CHECK(strcmp(registered_settings->settings[0].max_value, "-1") == 0);
    CHECK(strcmp(registered_settings->settings[12].max_value, "-1") == 0);
    il_command(true);
    CHECK(hardware_spindles == 1);
    return 0;
}
