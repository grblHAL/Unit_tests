#include "support/engine_host.h"
#include "ngc_params.h"
#include "check.h"

int main(void)
{
    engine_parser_prepare();
    gc_state.tool->tool_id = 3;
    gc_state.tool->radius = 4.5f;
    char offset[] = "G43.1X2Z4";
    CHECK(gc_execute_block(offset) == Status_OK);
    float value;
    CHECK(ngc_param_get(5400, &value)); NEAR(value, 3);
    CHECK(ngc_param_get(5410, &value)); NEAR(value, 9);
    CHECK(ngc_param_get(5401, &value)); NEAR(value, 2);
    CHECK(ngc_param_get(5402, &value)); NEAR(value, 0);
    CHECK(ngc_param_get(5403, &value)); NEAR(value, 4);
    CHECK(ngc_param_get(5404, &value)); NEAR(value, 0);
    CHECK(!ngc_param_set(5400, 8));
    CHECK(gc_state.tool->tool_id == 3);
    char cancel[] = "G49";
    CHECK(gc_execute_block(cancel) == Status_OK);
    CHECK(ngc_param_get(5401, &value)); NEAR(value, 0);
    CHECK(ngc_param_get(5403, &value)); NEAR(value, 0);
    return EXIT_SUCCESS;
}
