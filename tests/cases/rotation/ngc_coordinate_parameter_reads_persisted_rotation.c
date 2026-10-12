#include "support/engine_host.h"
#include "ngc_params.h"
#include "check.h"

int main(void)
{
    engine_parser_prepare(); coord_system_data_t offset={0}; offset.rotation=90*RADDEG;
    settings_write_coord_data(CoordinateSystem_G55,&offset); float value=0;
    CHECK(ngc_param_get(5250,&value)); NEAR(value,90*RADDEG);
    return EXIT_SUCCESS;
}
