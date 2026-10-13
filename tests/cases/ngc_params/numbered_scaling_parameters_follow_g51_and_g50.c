#include "support/engine_host.h"
#include "ngc_params.h"
#include "check.h"

int main(void)
{
    engine_parser_prepare();
    char scale[] = "G51X2Y3Z4";
    CHECK(gc_execute_block(scale) == Status_OK);
    float value;
    CHECK(ngc_param_get(5191, &value)); NEAR(value, 2);
    CHECK(ngc_param_get(5192, &value)); NEAR(value, 3);
    CHECK(ngc_param_get(5193, &value)); NEAR(value, 4);
    CHECK(ngc_param_get(5194, &value)); NEAR(value, 0);
    CHECK(!ngc_param_set(5191, 8));
    char cancel[] = "G50";
    CHECK(gc_execute_block(cancel) == Status_OK);
    for(unsigned id = 5191; id <= 5193; id++) {
        CHECK(ngc_param_get(id, &value)); NEAR(value, 1);
    }
    return EXIT_SUCCESS;
}
