#include "odometer_host.h"
int main(void)
{
 odometer_prepare(); hal.nvs.driver_area.size = NVS_SIZE - GRBL_NVS_SIZE;
 odometer_init(); CHECK(odometer_warnings == 1 && !hal.driver_cap.odometers && odometer_commands == NULL && transfers == 0); return 0;
}
