#include "support/spindle_sync_motion_host.h"
#include "check.h"

int main(void)
{
    prepare_spindle_sync_motion(); queue_spindle_sync_line(10,false); state_set(STATE_CYCLE);
    for(unsigned ticks=0;ticks<100;ticks++) { st_prep_buffer(); stepper_driver_interrupt_handler(); }
    CHECK(hal.stepper.pulse_start!=sync_motion_pulse); st_reset(); CHECK(hal.stepper.pulse_start==sync_motion_pulse);
    return EXIT_SUCCESS;
}
