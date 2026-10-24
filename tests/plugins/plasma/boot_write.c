#include "plasma_host.h"
int main(void)
{
    plasma_prepare(3, true);
    plasma_init();
    CHECK(plasma_details);
    plasma_details->restore();
    plasma_set(Setting_THC_Mode, PLASMA_BOOT_MODE);
    plasma_details->save();
    FILE *f = fopen("plasma.nvs", "wb");
    CHECK(f && fwrite(memory, 1, 16384, f) == 16384);
    CHECK(!fclose(f));
    return 0;
}
