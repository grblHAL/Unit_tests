#include "support/flow_host.h"
#include "ngc_params.h"

int main(void)
{
    prepare_flow();
    char name[] = "fixture";
    CHECK(ngc_named_param_set(name, 3));
    char block[] = "#<fixture>[10]";
    CHECK(gc_execute_block(block) == Status_BadNumberFormat);
    float value;
    CHECK(ngc_named_param_get(name, &value)); NEAR(value, 3);
    return EXIT_SUCCESS;
}
