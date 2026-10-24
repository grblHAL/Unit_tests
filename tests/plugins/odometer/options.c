#include "odometer_host.h"
int main(void)
{
 odometer_prepare(); odometer_init(); grbl.on_report_options(true); CHECK(strcmp(odometer_output, ",ODO") == 0);
 odometer_clear_output(); grbl.on_report_options(false); CHECK(strcmp(odometer_output, "Odometers") == 0); return 0;
}
