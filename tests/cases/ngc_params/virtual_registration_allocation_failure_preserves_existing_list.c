#include "support/virtual_param_host.h"
#include "support/malloc_failure_host.h"

static float second_value(void) { return 2; }
int main(void)
{
    engine_parser_prepare();
    CHECK(ngc_virtual_ro_param_add("_first", read_virtual_sensor));
    fail_malloc = true;
    CHECK(!ngc_virtual_ro_param_add("_second", second_value));
    fail_malloc = false;
    CHECK(failed_malloc_calls == 1);
    NEAR(read_virtual_name("_first"), 12.5f);
    char name[] = "_second";
    float value;
    CHECK(!ngc_named_param_get(name, &value));
    CHECK(ngc_virtual_ro_param_add("_second", second_value));
    NEAR(read_virtual_name("_second"), 2);
    NEAR(read_virtual_name("_first"), 12.5f);
    return EXIT_SUCCESS;
}
