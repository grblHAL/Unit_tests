#include <string.h>
#include "hal.h"
#include "check.h"

int main(void)
{
    CHECK(xbar_fn_to_signals_mask(Input_EStop).mask == (1U << Input_EStop));
    CHECK(xbar_fn_to_signals_mask(Input_Probe).mask == 0);
    CHECK(xbar_fn_to_signals_mask(Output_StepX).mask == 0);
    return EXIT_SUCCESS;
}
