#include "support/stepper_idle_host.h"
static void unexpected_delay(uint32_t milliseconds, delay_callback_ptr callback)
{
    (void)milliseconds; (void)callback;
    CHECK(false);
}
int main(void)
{
    prepare_stepper_idle();
    settings.stepper_enable_delay = 5;
    sys.steppers_enabled = true;
    hal.delay_ms = unexpected_delay;
    st_wake_up();
    CHECK(motor_enable_calls == 0 && wake_calls == 1);
    return EXIT_SUCCESS;
}
