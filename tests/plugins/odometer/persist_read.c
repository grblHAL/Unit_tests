#include "odometer_host.h"
int main(void)
{
 odometer_prepare(); FILE *file = fopen("nvs.dat", "rb"); CHECK(file); CHECK(fread(memory, 1, hal.nvs.size_max, file) == hal.nvs.size_max); CHECK(fclose(file) == 0);
 odometer_init(); CHECK(odometer_query(NULL) == Status_OK && strstr(odometer_output, "ODOMETERX 0.1") && strstr(odometer_output, "MOTORHRS 0:01"));
 CHECK(remove("nvs.dat") == 0); return 0;
}
