#include "support/engine_host.h"
#include "stepper2.h"
#include "check.h"
static uint64_t clock_us;
static unsigned pulses;
static uint64_t micros(void) { return clock_us; }
static void pulse(axes_signals_t axes, axes_signals_t direction)
{
    CHECK(axes.mask == X_AXIS_BIT);
    CHECK(direction.mask == 0 || direction.mask == X_AXIS_BIT);
    pulses++;
}
static st2_motor_t *prepare_motor(void)
{
    engine_prepare();
    hal.get_micros = micros;
    hal.stepper.output_step = pulse;
    st2_motor_t *motor = st2_motor_init(X_AXIS, false);
    CHECK(motor != NULL);
    CHECK(pulses == 0);
    return motor;
}

int main(void)
{
    st2_motor_t *motor = prepare_motor();
    CHECK(st2_motor_move(motor, 1, 100, Stepper2_Steps));
    CHECK(pulses == 1);
    CHECK(st2_get_position(motor) == 1);
    CHECK(!st2_motor_running(motor));
    return EXIT_SUCCESS;
}
