#include "support/engine_host.h"
#include "ngc_params.h"
#include "check.h"

int main(void)
{
    engine_parser_prepare();
    settings.flags.g92_is_volatile = false;
    sys.position[X_AXIS] = 800;
    gc_sync_position();
    char apply[] = "G92X2", suspend[] = "G92.2", restore[] = "G92.3";
    float value;
    CHECK(gc_execute_block(apply) == Status_OK);
    CHECK(ngc_param_get(5210, &value)); NEAR(value, 1);
    CHECK(ngc_param_get(5211, &value)); NEAR(value, 8);
    CHECK(gc_execute_block(suspend) == Status_OK);
    CHECK(ngc_param_get(5210, &value)); NEAR(value, 0);
    CHECK(ngc_param_get(5211, &value)); NEAR(value, 0);
    CHECK(gc_execute_block(restore) == Status_OK);
    CHECK(ngc_param_get(5210, &value)); NEAR(value, 1);
    CHECK(ngc_param_get(5211, &value)); NEAR(value, 8);
    return EXIT_SUCCESS;
}
