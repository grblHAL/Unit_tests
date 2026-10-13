#include "support/flow_host.h"
#include "ngc_params.h"

int main(void)
{
    prepare_flow();
    CHECK(ngc_param_set(100, 3));
    CHECK(ngc_param_set(101, 7));
    char block[] = "#100=10#101=[#100+2]";
    CHECK(gc_execute_block(block) == Status_OK);
    float value;
    CHECK(ngc_param_get(100, &value)); NEAR(value, 10);
    CHECK(ngc_param_get(101, &value)); NEAR(value, 5);
    return EXIT_SUCCESS;
}
