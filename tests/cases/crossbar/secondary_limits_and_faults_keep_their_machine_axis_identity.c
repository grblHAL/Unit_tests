#include "hal.h"
#include "check.h"
int main(void)
{
    const pin_function_t functions[][2] = {
        {Input_LimitX_2, Input_MotorFaultX2},
        {Input_LimitY_2, Input_MotorFaultY2},
        {Input_LimitZ_2, Input_MotorFaultZ2}
    };
    const unsigned masks[] = {1, 2, 4};
    for(unsigned axis = 0; axis < 3; axis++)
        for(unsigned signal = 0; signal < 2; signal++) {
            CHECK(xbar_fn_to_axismask(functions[axis][signal]).mask == masks[axis]);
            CHECK(xbar_fn_for_secondary_motor(functions[axis][signal]));
        }
    return EXIT_SUCCESS;
}
