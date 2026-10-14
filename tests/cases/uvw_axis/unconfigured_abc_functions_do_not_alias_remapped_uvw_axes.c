#include "hal.h"
#include "check.h"
int main(void)
{
    const pin_function_t functions[] = {
        Input_LimitA, Input_LimitA_Max, Input_HomeA, Input_MotorFaultA, Output_StepperEnableA,
        Input_LimitB, Input_LimitB_Max, Input_HomeB, Input_MotorFaultB, Output_StepperEnableB,
        Input_LimitC, Input_LimitC_Max, Input_HomeC, Input_MotorFaultC, Output_StepperEnableC,
        Output_StepperEnableAB
    };
    for(unsigned i = 0; i < sizeof(functions) / sizeof(functions[0]); i++)
        CHECK(xbar_fn_to_axismask(functions[i]).mask == 0);
    CHECK(xbar_fn_to_axismask(Output_StepperEnable).mask == 63);
    return EXIT_SUCCESS;
}
