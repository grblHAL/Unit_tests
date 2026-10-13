#include "support/virtual_param_host.h"

int main(void)
{
    engine_parser_prepare();
    CHECK(ngc_virtual_ro_param_add("_sensor", read_virtual_sensor));
    NEAR(read_virtual_name("_sensor"), 12.5f);
    virtual_sensor_value = 33.25f;
    NEAR(read_virtual_name("_sensor"), 33.25f);
    char name[] = "_sensor";
    CHECK(!ngc_named_param_set(name, 99));
    NEAR(virtual_sensor_value, 33.25f);
    return EXIT_SUCCESS;
}
