#include "support/jog_motion_host.h"
#include "check.h"

int main(void)
{
    prepare_jog_motion(); CHECK(!gc_state.modal.units_imperial); CHECK(!gc_state.modal.distance_incremental);
    CHECK(system_command("$J=G20G91X1F10")==Status_OK); plan_block_t *block=plan_get_current_block(); NEAR(block->programmed_rate,254);
    CHECK(!gc_state.modal.units_imperial); CHECK(!gc_state.modal.distance_incremental); NEAR(gc_state.position[X_AXIS],25.4f);
    finish_jog_motion(); CHECK(axis_pulses[X_AXIS]==2032); CHECK(physical_position[X_AXIS]==2032);
    return EXIT_SUCCESS;
}
