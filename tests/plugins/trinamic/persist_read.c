#include "tmc_host.h"
int main(void)
{
    tmc_prepare();
    FILE *f = fopen("tmc.nvs", "rb");
    CHECK(f && fread(memory, 1, 16384, f) == 16384);
    CHECK(!fclose(f));
    tmc_start();
    CHECK(tmc_drivers[1]->get_config(1)->current == 750 &&
          tmc_drivers[1]->get_config(1)->microsteps == 32);
    CHECK(tmc_drivers[0]->get_config(0)->current == 500);
    CHECK(!remove("tmc.nvs"));
    return 0;
}
