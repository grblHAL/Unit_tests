#include "support/flow_static_macro_host.h"
int main(void)
{
    const char *name = "fixture_with_a_long_name_for_workholding_setup_and_tool_checks";
    prepare_static_macro_named(name);
    CHECK(ngc_param_set(1, 99));
    char call[128] = "O<";
    strcat(call, name);
    strcat(call, ">CALL[12][34]");
    CHECK(gc_execute_block(call) == Status_OK);
    CHECK(hal.stream.file != NULL && ngc_call_level() == 1);
    float value;
    CHECK(ngc_param_get(1, &value)); NEAR(value, 12);
    CHECK(ngc_param_get(2, &value)); NEAR(value, 34);
    char end[128] = "O<";
    strcat(end, name);
    strcat(end, ">ENDSUB[7]");
    CHECK(gc_execute_block(end) == Status_OK);
    CHECK(file_closes == 1 && hal.stream.file == NULL && ngc_call_level() == 0);
    CHECK(ngc_param_get(1, &value)); NEAR(value, 99);
    char result[] = "_value";
    CHECK(ngc_named_param_get(result, &value)); NEAR(value, 7);
    return EXIT_SUCCESS;
}
