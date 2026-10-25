#include "support/engine_host.h"
#include "ngc_params.h"
#include "check.h"
int main(void)
{
    engine_parser_prepare();
    sys.position[X_AXIS] = 2032;
    char block[] = "G20";
    CHECK(gc_execute_block(block) == Status_OK);
    CHECK(gc_state.modal.units_imperial);
    char name[] = "_abs_x";
    float value;
    CHECK(ngc_named_param_get(name, &value));
    fprintf(stderr, "inch position=%g, expected=1\n", (double)value);
    NEAR(value, 1.0f);
    char absent_a[] = "_abs_a", absent_w[] = "_abs_w";
    CHECK(ngc_named_param_get(absent_a, &value)); NEAR(value, 0);
    CHECK(ngc_named_param_get(absent_w, &value)); NEAR(value, 0);
    return EXIT_SUCCESS;
}
