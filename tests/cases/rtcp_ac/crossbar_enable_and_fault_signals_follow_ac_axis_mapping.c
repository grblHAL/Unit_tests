#include "hal.h"
#include "check.h"
int main(void)
{
    CHECK(xbar_fn_to_axismask(Output_StepperEnableAB).mask == 8);
    CHECK(xbar_fn_to_axismask(Input_LimitA).mask == 8);
    CHECK(xbar_fn_to_axismask(Input_LimitC).mask == 16);
    CHECK(xbar_fn_to_axismask(Input_MotorFaultC).mask == 16);
    CHECK(xbar_fn_to_axismask(Output_StepperEnableC).mask == 16);
    CHECK(xbar_fn_to_axismask(Input_LimitB).mask == 0);
    CHECK(xbar_fn_to_axismask(Output_StepperEnable).mask == 31);
    return EXIT_SUCCESS;
}
