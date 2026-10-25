#include "plasma_host.h"
int main(void)
{
    plasma_prepare(3, true);
    plasma_init();
    CHECK(plasma_details);
    plasma_details->restore();
    plasma_set(Setting_THC_Mode, PLASMA_BOOT_MODE);
#if PLASMA_BOOT_MODE == 1
    plasma_set_port(Setting_Arc_VoltagePort, 0);
#endif
    plasma_details->save();
    FILE *f = fopen("plasma.nvs", "wb");
    CHECK(f && fwrite(memory, 1, 16384, f) == 16384);
    CHECK(!fclose(f));
    return 0;
}
