#include "odometer_host.h"
int main(void)
{
 odometer_prepare(); odometer_init(); odometer_move(8000, 0, 0, 60000);
 FILE *file = fopen("nvs.dat", "wb"); CHECK(file); CHECK(fwrite(memory, 1, hal.nvs.size_max, file) == hal.nvs.size_max); CHECK(fclose(file) == 0); return 0;
}
