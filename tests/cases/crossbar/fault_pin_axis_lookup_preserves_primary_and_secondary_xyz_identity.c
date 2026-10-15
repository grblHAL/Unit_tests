#include "hal.h"
#include "check.h"
int main(void)
{
    const pin_function_t pins[] = {Input_MotorFaultX, Input_MotorFaultY, Input_MotorFaultZ,
        Input_MotorFaultX2, Input_MotorFaultY2, Input_MotorFaultZ2};
    const uint8_t expected[] = {0, 1, 2, 0, 1, 2};
    for(unsigned i = 0; i < sizeof(pins) / sizeof(pins[0]); i++)
        CHECK(xbar_fault_pin_to_axis(pins[i]) == expected[i]);
    return EXIT_SUCCESS;
}
