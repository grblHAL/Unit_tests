#include "support/flow_host.h"
#include "ngc_params.h"

int main(void)
{
    prepare_flow();
    char block[] = "#<fixture>=[2*3+1]";
    CHECK(gc_execute_block(block) == Status_OK);
    char name[] = "fixture";
    float value;
    CHECK(ngc_named_param_get(name, &value)); NEAR(value, 7);
    return EXIT_SUCCESS;
}
