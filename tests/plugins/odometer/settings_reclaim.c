#include "odometer_host.h"
int main(void)
{
 odometer_prepare(); odometer_init(); odometer_move(8000, 0, 0, 1000);
 odometer_replace_pulse = true; grbl.on_settings_changed(&settings, (settings_changed_flags_t){0});
 odometer_move(8000, 0, 0, 1000); CHECK(odometer_settings_calls == 1 && odometer_alternate_calls == 8000 && odometer_pulse_counts[0] == 16000);
 CHECK(odometer_query(NULL) == Status_OK && strstr(odometer_output, "ODOMETERX 0.2")); return 0;
}
