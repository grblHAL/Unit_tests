#include "support/flow_host.h"
#include "ngc_params.h"

int main(void)
{
    prepare_flow();
    float before, after;
    CHECK(ngc_param_get(5220, &before));
    char block[] = "#5220=2";
    CHECK(gc_execute_block(block) == Status_GcodeValueOutOfRange);
    CHECK(ngc_param_get(5220, &after)); NEAR(after, before);
    return EXIT_SUCCESS;
}
