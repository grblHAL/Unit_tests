#include "stepper_host.h"
int main(void)
{
    stepper_timer_available = true;
    stepper_timer_claim_ok = false;
    stepper_clock_ok = false;
    stepper_prepare();
    CHECK(!stepper_settings && stepper_warnings == 1 && stepper_timer_claims == 2);
    CHECK(!stepper_pulses && !stepper_timer_starts);
    return 0;
}
