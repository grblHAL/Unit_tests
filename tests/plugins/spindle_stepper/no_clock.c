#include "stepper_host.h"
int main(void)
{
    stepper_clock_ok = false;
    stepper_prepare();
    CHECK(!stepper_settings && stepper_warnings == 1 && !spindle_get_hal(0, SpindleHAL_Raw));
    return 0;
}
