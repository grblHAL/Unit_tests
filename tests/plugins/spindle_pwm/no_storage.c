#include "pwm_host.h"
int main(void)
{
    pwm_storage = false;
    pwm_prepare(2);
    CHECK(!pwm_settings && pwm_warnings == 1 && !spindle_get(0));
    CHECK(!pwm_analog_calls && !pwm_writes);
    return 0;
}
