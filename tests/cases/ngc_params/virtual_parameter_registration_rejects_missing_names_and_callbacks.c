#include "support/virtual_param_host.h"

int main(void)
{
    engine_parser_prepare();
    CHECK(!ngc_virtual_ro_param_add(NULL, read_virtual_sensor));
    CHECK(!ngc_virtual_ro_param_add("", read_virtual_sensor));
    CHECK(!ngc_virtual_ro_param_add("local", read_virtual_sensor));
    CHECK(!ngc_virtual_ro_param_add("_sensor", NULL));
    CHECK(!ngc_virtual_rw_param_add("_sensor", read_virtual_sensor, NULL));
    CHECK(!ngc_virtual_rw_param_add("_sensor", NULL, write_virtual_sensor));
    CHECK(ngc_virtual_ro_param_add("_sensor", read_virtual_sensor));
    NEAR(read_virtual_name("_sensor"), 12.5f);
    return EXIT_SUCCESS;
}
