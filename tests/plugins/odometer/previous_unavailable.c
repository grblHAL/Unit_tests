#include "odometer_host.h"
int main(void)
{
 odometer_prepare(); odometer_init(); char previous[] = "PREV";
 CHECK(odometer_query(previous) == Status_OK && strstr(odometer_output, "Previous odometer values not available"));
 CHECK(hal.driver_cap.odometers && odometer_query(NULL) == Status_OK); return 0;
}
