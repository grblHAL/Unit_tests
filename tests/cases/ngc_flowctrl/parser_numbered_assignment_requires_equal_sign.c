#include "support/flow_host.h"
#include "ngc_params.h"

int main(void)
{
    prepare_flow();
    CHECK(ngc_param_set(100, 3));
    char block[] = "#100[10]";
    CHECK(gc_execute_block(block) == Status_BadNumberFormat);
    float value;
    CHECK(ngc_param_get(100, &value)); NEAR(value, 3);
    return EXIT_SUCCESS;
}
