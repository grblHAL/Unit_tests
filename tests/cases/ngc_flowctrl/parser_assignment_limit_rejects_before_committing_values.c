#include "support/flow_host.h"
#include "ngc_params.h"

int main(void)
{
    prepare_flow();
    for(unsigned id = 100; id < 111; id++) CHECK(ngc_param_set(id, 3));
    char block[] = "#100=1#101=1#102=1#103=1#104=1#105=1#106=1#107=1#108=1#109=1#110=1";
    CHECK(gc_execute_block(block) == Status_BadNumberFormat);
    for(unsigned id = 100; id < 111; id++) {
        float value;
        CHECK(ngc_param_get(id, &value)); NEAR(value, 3);
    }
    return EXIT_SUCCESS;
}
