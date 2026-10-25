#include "hal.h"
#include "check.h"
int main(void)
{
    CHECK(xbar_fn_to_axismask(Output_StepperEnableAB).mask == 24);
    CHECK(xbar_fn_to_axismask(Output_StepperEnableXY).mask == 3);
    CHECK(xbar_fn_to_axismask(Output_StepperEnable).mask == 255);
    CHECK(xbar_fn_to_axismask(Input_Probe).mask == 0);
    return EXIT_SUCCESS;
}
