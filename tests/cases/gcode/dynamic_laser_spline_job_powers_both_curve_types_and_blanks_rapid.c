#include "support/laser_stepper_host.h"

static unsigned foreground_calls, powered_steps;
static void observe_laser_step(stepper_t *stepper)
{
    if(stepper->step_out.mask && laser_last_driver_level > 0)
        powered_steps++;
    pulse_driver(stepper);
}
static void execute_foreground(sys_state_t state)
{
    CHECK(++foreground_calls < 100000);
    if(state == STATE_CYCLE || state == STATE_HOLD)
        stepper_driver_interrupt_handler();
}

int main(void)
{
    prepare_laser_stepper();
    hal.stepper.pulse_start = observe_laser_step;
    grbl.on_execute_realtime = execute_foreground;
    CHECK(laser_block("M4S500") == Status_OK);
    CHECK(laser_block("G5X1Y1I0J1P-1Q0F100") == Status_OK);
    CHECK(protocol_buffer_synchronize());
    CHECK(physical_position[X_AXIS] == 80 && physical_position[Y_AXIS] == 80);
    CHECK(powered_steps > 0);
    unsigned cubic_powered_steps = powered_steps;
    CHECK(laser_block("G5.1X2Y0I1J0") == Status_OK);
    CHECK(protocol_buffer_synchronize());
    CHECK(physical_position[X_AXIS] == 160 && physical_position[Y_AXIS] == 0);
    CHECK(powered_steps > cubic_powered_steps);
    unsigned cutting_powered_steps = powered_steps;
    CHECK(laser_block("G0X3") == Status_OK);
    CHECK(protocol_buffer_synchronize());
    CHECK(physical_position[X_AXIS] == 240 && physical_position[Y_AXIS] == 0);
    CHECK(powered_steps == cutting_powered_steps && laser_last_driver_level == 0);
    CHECK(axis_pulses[Z_AXIS] == 0 && !sys.abort && sys.alarm == Alarm_None);
    CHECK(laser_block("M5") == Status_OK);
    CHECK(!laser_output_state.on && plan_get_current_block() == NULL);
    return EXIT_SUCCESS;
}
