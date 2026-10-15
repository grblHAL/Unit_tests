#include "hal.h"
#include "check.h"
int main(void)
{
    const pin_function_t probes[] = {Input_Probe, Input_Probe2, Input_Toolsetter};
    const pin_function_t encoders[] = {Input_QEI_A, Input_QEI_B, Input_QEI_Select};
    for(unsigned i = 0; i < 3; i++) {
        CHECK(xbar_is_probe_in(probes[i]));
        CHECK(!xbar_is_encoder_in(probes[i]) && !xbar_is_motor_fault_in(probes[i]));
        CHECK(xbar_is_encoder_in(encoders[i]));
        CHECK(!xbar_is_probe_in(encoders[i]) && !xbar_is_motor_fault_in(encoders[i]));
    }
    CHECK(xbar_is_motor_fault_in(Input_MotorFaultX));
    CHECK(xbar_is_motor_fault_in(Input_MotorFaultZ2));
    CHECK(!xbar_is_probe_in(Input_LimitX) && !xbar_is_encoder_in(Input_LimitX));
    CHECK(!xbar_is_motor_fault_in(Input_LimitX));
    CHECK(!xbar_is_probe_in(Input_Aux0) && !xbar_is_encoder_in(Input_Aux0));
    CHECK(!xbar_is_motor_fault_in(Input_Aux0));
    return EXIT_SUCCESS;
}
