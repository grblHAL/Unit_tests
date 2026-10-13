#include "support/virtual_param_host.h"

int main(void)
{
    engine_parser_prepare();
    CHECK(ngc_virtual_rw_param_add("_sensor", read_virtual_sensor, write_virtual_sensor));
    int context;
    CHECK(ngc_call_push(&context));
    NEAR(read_virtual_name("_sensor"), 12.5f);
    char name[] = "_sensor";
    CHECK(ngc_named_param_set(name, 42));
    (void)ngc_call_pop();
    CHECK(ngc_call_level() == 0);
    NEAR(read_virtual_name("_sensor"), 42);
    CHECK(virtual_writes == 1);
    return EXIT_SUCCESS;
}
