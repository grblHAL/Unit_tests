#include "odometer_host.h"
int main(void)
{
 odometer_prepare(); odometer_init(); odometer_move(8000, 0, 0, 60000);
 char reset[] = "rst", previous[] = "prev", unknown[] = "UNKNOWN";
 CHECK(odometer_query(reset) == Status_OK); CHECK(odometer_query(NULL) == Status_OK && strstr(odometer_output, "ODOMETERX 0.0") && strstr(odometer_output, "MOTORHRS 0:00"));
 odometer_clear_output(); CHECK(odometer_query(previous) == Status_OK && strstr(odometer_output, "ODOMETERX 0.1") && strstr(odometer_output, "MOTORHRS 0:01"));
 CHECK(odometer_query(unknown) == Status_Unhandled); return 0;
}
