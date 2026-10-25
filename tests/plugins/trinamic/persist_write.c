#include "tmc_host.h"
int main(void)
{
    tmc_prepare();
    tmc_start();
    CHECK(tmc_set(Setting_AxisStepperCurrent, Y_AXIS, 750) == Status_OK &&
          tmc_set(Setting_AxisMicroSteps, Y_AXIS, 32) == Status_OK);
    tmc_settings->save();
    FILE *f = fopen("tmc.nvs", "wb");
    CHECK(f && fwrite(memory, 1, 16384, f) == 16384);
    CHECK(!fclose(f));
    return 0;
}
