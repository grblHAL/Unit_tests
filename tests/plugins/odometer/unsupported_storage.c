#include "odometer_host.h"
int main(void)
{
 odometer_prepare(); hal.nvs.type = NVS_Flash; on_state_change_ptr before = grbl.on_state_change;
 odometer_init(); CHECK(odometer_warnings == 1 && !hal.driver_cap.odometers && odometer_commands == NULL && grbl.on_state_change == before);
 CHECK(transfers == 0); return 0;
}
