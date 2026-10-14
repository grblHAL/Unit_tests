#include "hal.h"
#include "check.h"
int main(void)
{
    const pin_function_t functions[][5] = {
        {Input_LimitU, Input_LimitU_Max, Input_HomeU, Input_MotorFaultU, Output_StepperEnableU},
        {Input_LimitV, Input_LimitV_Max, Input_HomeV, Input_MotorFaultV, Output_StepperEnableV},
        {Input_LimitW, Input_LimitW_Max, Input_HomeW, Input_MotorFaultW, Output_StepperEnableW}
    };
    const unsigned masks[] = {8, 16, 32};
    for(unsigned axis = 0; axis < 3; axis++)
        for(unsigned signal = 0; signal < 5; signal++)
            CHECK(xbar_fn_to_axismask(functions[axis][signal]).mask == masks[axis]);
    return EXIT_SUCCESS;
}
