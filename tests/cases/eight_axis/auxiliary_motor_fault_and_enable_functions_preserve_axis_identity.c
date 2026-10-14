#include "hal.h"
#include "check.h"
int main(void)
{
    const pin_function_t functions[][2] = {
        {Input_MotorFaultA, Output_StepperEnableA},
        {Input_MotorFaultB, Output_StepperEnableB},
        {Input_MotorFaultC, Output_StepperEnableC},
        {Input_MotorFaultU, Output_StepperEnableU},
        {Input_MotorFaultV, Output_StepperEnableV}
    };
    const unsigned masks[] = {8, 16, 32, 64, 128};
    for(unsigned axis = 0; axis < 5; axis++)
        for(unsigned signal = 0; signal < 2; signal++)
            CHECK(xbar_fn_to_axismask(functions[axis][signal]).mask == masks[axis]);
    return EXIT_SUCCESS;
}
