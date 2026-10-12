#include "support/flow_static_macro_host.h"
#include "check.h"
int main(void)
{
    prepare_static_macro();
    CHECK(ngc_param_set(1, 99));
    CHECK(flow_command(static_macro_label, "CALL[12]") == Status_OK);
    CHECK(flow_command(static_macro_label, "ENDSUB[7]") == Status_OK);
    CHECK(file_closes == 1);
    CHECK(hal.stream.file == NULL);
    CHECK(ngc_call_level() == 0);
    float value;
    CHECK(ngc_param_get(1, &value));
    NEAR(value, 99);
    char name[] = "_value";
    CHECK(ngc_named_param_get(name, &value));
    NEAR(value, 7);
    return EXIT_SUCCESS;
}
