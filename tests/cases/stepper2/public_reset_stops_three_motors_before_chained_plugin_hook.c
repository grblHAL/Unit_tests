#include "support/secondary_stepper_host.h"
#include "motion_control.h"
#include "state_machine.h"

static st2_motor_t *active_motors[3];
static unsigned plugin_resets, pulses[3];
static control_signals_t read_controls(void) { return (control_signals_t){0}; }
static void output_step(axes_signals_t axes, axes_signals_t direction)
{
    CHECK(axes.mask == X_AXIS_BIT || axes.mask == Y_AXIS_BIT || axes.mask == Z_AXIS_BIT);
    CHECK(direction.mask == 0 || direction.mask == axes.mask);
    for(unsigned axis = 0; axis < 3; axis++) if(axes.mask & (1u << axis)) pulses[axis]++;
}
static void plugin_reset(void)
{
    plugin_resets++;
    for(unsigned axis = 0; axis < 3; axis++) CHECK(!st2_motor_running(active_motors[axis]));
}
int main(void)
{
    engine_prepare();
    state_set(STATE_IDLE);
    hal.get_micros = motor_micros;
    hal.stepper.output_step = output_step;
    hal.control.get_state = read_controls;
    grbl.on_reset = plugin_reset;
    for(unsigned axis = 0; axis < 3; axis++) {
        settings.axis[axis].acceleration = 36000;
        CHECK((active_motors[axis] = st2_motor_init(axis, false)) != NULL);
        CHECK(st2_motor_move(active_motors[axis], 0, 100, Stepper2_InfiniteSteps));
        tick_motor(active_motors[axis]);
        CHECK(st2_motor_running(active_motors[axis]) && pulses[axis] > 0);
    }
    unsigned before[3];
    memcpy(before, pulses, sizeof(before));
    mc_reset();
    CHECK(plugin_resets == 1 && (sys.rt_exec_state & EXEC_RESET));
    for(unsigned axis = 0; axis < 3; axis++) {
        tick_motor(active_motors[axis]);
        CHECK(pulses[axis] == before[axis]);
        NEAR(st2_get_speed(active_motors[axis]), 0);
    }
    mc_reset();
    CHECK(plugin_resets == 1);
    return EXIT_SUCCESS;
}
