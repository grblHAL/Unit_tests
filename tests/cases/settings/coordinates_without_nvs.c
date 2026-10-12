#include "support/engine_host.h"
#include "nvs.h"
#include <string.h>
#include "check.h"

int main(void)
{
    engine_prepare();
    coord_system_data_t result;
    memset(&result, 0x55, sizeof(result));
    hal.nvs.type = NVS_None;
    CHECK(!settings_read_coord_data(CoordinateSystem_G54, &result));
    for(unsigned i = 0; i < N_AXIS; i++) CHECK(result.coord.values[i] == 0);
    return EXIT_SUCCESS;
}
