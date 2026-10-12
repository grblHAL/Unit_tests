#include <string.h>
#include "hal.h"
#include "check.h"

int main(void)
{
    CHECK(xbar_fn_for_secondary_motor(Input_LimitX_2));
    CHECK(xbar_fn_for_secondary_motor(Input_MotorFaultZ2));
    CHECK(!xbar_fn_for_secondary_motor(Input_LimitX)); CHECK(!xbar_fn_for_secondary_motor(Input_Probe));
    return EXIT_SUCCESS;
}
