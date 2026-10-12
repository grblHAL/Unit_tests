#include "support/engine_host.h"
#include "ngc_params.h"
#include "check.h"

int main(void)
{
    engine_parser_prepare();
    float value;
    char first[] = "G54", second[] = "G55", last[] = "G59.3";
    CHECK(gc_execute_block(first) == Status_OK);
    CHECK(ngc_param_get(5220, &value)); NEAR(value, 1);
    CHECK(gc_execute_block(second) == Status_OK);
    CHECK(ngc_param_get(5220, &value)); NEAR(value, 2);
    CHECK(gc_execute_block(last) == Status_OK);
    CHECK(ngc_param_get(5220, &value)); NEAR(value, 9);
    return EXIT_SUCCESS;
}
