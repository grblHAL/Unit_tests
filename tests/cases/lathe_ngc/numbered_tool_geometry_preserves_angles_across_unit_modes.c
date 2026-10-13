#include "support/css_host.h"
#include "ngc_params.h"

int main(void)
{
    prepare_css_parser(true);
    tool_data_t tool = {.tool_id = 2, .front_angle = 30, .back_angle = 12,
        .orientation = ToolPos2_45};
    gc_state.tool = &tool;
    float value;
    CHECK(ngc_param_get(5411, &value)); NEAR(value, 30);
    CHECK(ngc_param_get(5412, &value)); NEAR(value, 12);
    CHECK(ngc_param_get(5413, &value)); NEAR(value, 2);
    CHECK(css_block("G20") == Status_OK);
    CHECK(ngc_param_get(5411, &value)); NEAR(value, 30);
    CHECK(ngc_param_get(5412, &value)); NEAR(value, 12);
    CHECK(ngc_param_get(5413, &value)); NEAR(value, 2);
    CHECK(!ngc_param_set(5411, 45));
    CHECK(!ngc_param_set(5412, 45));
    CHECK(!ngc_param_set(5413, 9));
    NEAR(tool.front_angle, 30); NEAR(tool.back_angle, 12);
    CHECK(tool.orientation == ToolPos2_45);
    return EXIT_SUCCESS;
}
