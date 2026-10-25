#include "odometer_host.h"
int main(void)
{
 odometer_prepare(); odometer_init(); CHECK(hal.driver_cap.odometers && odometer_warnings == 0);
 odometer_move(8000, 16000, 24000, 60000); CHECK(odometer_query(NULL) == Status_OK);
 CHECK(strstr(odometer_output, "MOTORHRS 0:01") && strstr(odometer_output, "ODOMETERX 0.1") && strstr(odometer_output, "ODOMETERY 0.2") && strstr(odometer_output, "ODOMETERZ 0.3"));
 CHECK(odometer_pulse_counts[0] == 8000 && odometer_pulse_counts[1] == 16000 && odometer_pulse_counts[2] == 24000);
 unsigned before = transfers; grbl.on_state_change(STATE_IDLE); CHECK(transfers == before && odometer_state_calls == 3); return 0;
}
