#include "support/virtual_param_host.h"

static float second_value(void) { return 2; }
static float third_value(void) { return 3; }
int main(void)
{
    engine_parser_prepare();
    CHECK(ngc_virtual_ro_param_add("_first", read_virtual_sensor));
    CHECK(ngc_virtual_ro_param_add("_second", second_value));
    CHECK(ngc_virtual_ro_param_add("_third", third_value));
    CHECK(!ngc_virtual_ro_param_add("_first", third_value));
    NEAR(read_virtual_name("_first"), 12.5f);
    NEAR(read_virtual_name("_second"), 2);
    NEAR(read_virtual_name("_third"), 3);
    char missing[] = "_missing";
    float value;
    CHECK(!ngc_named_param_get(missing, &value));
    return EXIT_SUCCESS;
}
