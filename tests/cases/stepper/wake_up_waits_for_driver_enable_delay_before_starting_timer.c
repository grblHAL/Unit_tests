#include "support/stepper_idle_host.h"
static unsigned enable_delay_calls;
static void enable_delay(uint32_t milliseconds, delay_callback_ptr callback)
{
    CHECK(milliseconds == 5);
    CHECK(callback == NULL);
    CHECK(motor_enable_calls == 1);
    CHECK(last_motor_enable.mask == AXES_BITMASK && !last_motor_hold);
    CHECK(wake_calls == 0);
    enable_delay_calls++;
}
int main(void)
{
    prepare_stepper_idle();
    settings.stepper_enable_delay = 5;
    hal.delay_ms = enable_delay;
    st_wake_up();
    CHECK(enable_delay_calls == 1 && wake_calls == 1);
    return EXIT_SUCCESS;
}
