#include "support/engine_host.h"
#include "ngc_params.h"
#include "check.h"

int main(void)
{
    engine_parser_prepare();
    gc_state.position[X_AXIS] = 15;
    sys.position[X_AXIS] = 15 * settings.axis[X_AXIS].steps_per_mm;
    char work[] = "G10L2P1X2";
    CHECK(gc_execute_block(work) == Status_OK);
    char tool[] = "G43.1X3";
    CHECK(gc_execute_block(tool) == Status_OK);
    char local[] = "G92X6";
    CHECK(gc_execute_block(local) == Status_OK);
    float value;
    CHECK(ngc_param_get(5420, &value)); NEAR(value, 6);
    sys.position[X_AXIS] += 8 * settings.axis[X_AXIS].steps_per_mm;
    CHECK(ngc_param_get(5420, &value)); NEAR(value, 14);
    CHECK(ngc_param_get(5423, &value)); NEAR(value, 0);
    CHECK(ngc_param_get(5428, &value)); NEAR(value, 0);
    char inches[] = "G20";
    CHECK(gc_execute_block(inches) == Status_OK);
    CHECK(ngc_param_get(5420, &value)); NEAR(value, 14 / 25.4f);
    CHECK(ngc_param_get(5423, &value)); NEAR(value, 0);
    CHECK(ngc_param_get(5428, &value)); NEAR(value, 0);
    return EXIT_SUCCESS;
}
