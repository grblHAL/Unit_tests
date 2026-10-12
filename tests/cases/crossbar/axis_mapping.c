#include <string.h>
#include "hal.h"
#include "check.h"

int main(void)
{
    CHECK(xbar_fn_to_axismask(Input_LimitX).mask == 1);
    CHECK(xbar_fn_to_axismask(Input_LimitY_Max).mask == 2);
    CHECK(xbar_fn_to_axismask(Input_HomeZ).mask == 4);
    CHECK(xbar_fn_to_axismask(Output_StepperEnable).mask == AXES_BITMASK);
    CHECK(xbar_fn_to_axismask(Output_StepperEnableXY).mask == 3);
    CHECK(xbar_fn_to_axismask(Input_Probe).mask == 0);
    return EXIT_SUCCESS;
}
