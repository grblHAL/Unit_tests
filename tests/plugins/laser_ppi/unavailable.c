#include "ppi_host.h"
int main(void)
{
    ppi_prepare(false, false);
    CHECK(!hal.driver_cap.laser_ppi_mode);
    parser_block_t block = {.user_mcode = LaserPPI_Enable, .words.p = On, .values.p = 1};
    CHECK(grbl.user_mcode.validate(&block) == Status_GcodeUnsupportedCommand);
    return 0;
}
