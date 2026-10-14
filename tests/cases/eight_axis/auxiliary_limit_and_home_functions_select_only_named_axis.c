#include "hal.h"
#include "check.h"
int main(void)
{
    const pin_function_t limits[][3] = {
        {Input_LimitA, Input_LimitA_Max, Input_HomeA},
        {Input_LimitB, Input_LimitB_Max, Input_HomeB},
        {Input_LimitC, Input_LimitC_Max, Input_HomeC},
        {Input_LimitU, Input_LimitU_Max, Input_HomeU},
        {Input_LimitV, Input_LimitV_Max, Input_HomeV}
    };
    const unsigned masks[] = {8, 16, 32, 64, 128};
    for(unsigned axis = 0; axis < 5; axis++)
        for(unsigned signal = 0; signal < 3; signal++)
            CHECK(xbar_fn_to_axismask(limits[axis][signal]).mask == masks[axis]);
    return EXIT_SUCCESS;
}
