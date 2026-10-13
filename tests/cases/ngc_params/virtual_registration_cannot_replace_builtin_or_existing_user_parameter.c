#include "support/virtual_param_host.h"

int main(void)
{
    engine_parser_prepare();
    CHECK(!ngc_virtual_ro_param_add("_metric", read_virtual_sensor));
    NEAR(read_virtual_name("_metric"), 1);
    char name[] = "_saved";
    CHECK(ngc_named_param_set(name, 42));
    CHECK(!ngc_virtual_rw_param_add("_saved", read_virtual_sensor, write_virtual_sensor));
    NEAR(read_virtual_name("_saved"), 42);
    CHECK(virtual_writes == 0);
    return EXIT_SUCCESS;
}
