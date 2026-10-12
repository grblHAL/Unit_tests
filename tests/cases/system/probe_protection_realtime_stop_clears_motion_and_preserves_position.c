#include "support/control_irq_host.h"
#include "check.h"

int main(void)
{
    prepare_control_irq_cycle();
    for(unsigned tick=0; tick<10000 && sys.position[X_AXIS]<20; tick++) {
        st_prep_buffer();
        stepper_driver_interrupt_handler();
    }
    CHECK(sys.position[X_AXIS] == 20);
    int32_t physical_before_stop = physical_position[X_AXIS];
    unsigned pulses_before_stop = axis_pulses[X_AXIS];
    CHECK(labs(physical_before_stop - sys.position[X_AXIS]) <= 1);
    irq_probe_input = true;
    control_interrupt_handler((control_signals_t){.probe_triggered=true});
    CHECK(!protocol_execute_realtime());
    CHECK(state_get() == STATE_ALARM);
    CHECK(sys.alarm == Alarm_ProbeProtect);
    CHECK(plan_get_current_block() == NULL);
    CHECK(!st_is_stepping());
    CHECK(sys.position[X_AXIS] == 20);
    CHECK(physical_position[X_AXIS] == physical_before_stop);
    CHECK(axis_pulses[X_AXIS] == pulses_before_stop);
    CHECK(sys.position_lost);
    NEAR(gc_state.position[X_AXIS], .25f);
    CHECK(control_driver_reset_calls == 1);
    return EXIT_SUCCESS;
}
