#include "support/explicit_probe_program_host.h"
int main(void)
{
    prepare_explicit_probe();
    CHECK(hal.probe.select(Probe_2));
    explicit_selection_calls = 0;
    CHECK(explicit_probe_block("G20G91") == Status_OK);
    CHECK(explicit_probe_block("G38.2X0.0393700787F3.93700787P1") == Status_OK);
    check_explicit_contact(Probe_Toolsetter, Probe_2, 64);
    CHECK(explicit_selection_calls == 2);
    CHECK(gc_state.modal.units_imperial && gc_state.modal.distance_incremental);
    NEAR(gc_state.feed_rate, 100);
    int32_t contacted = physical_position[X_AXIS];
    CHECK(explicit_probe_block("G0X-0.01") == Status_OK);
    CHECK(protocol_buffer_synchronize());
    CHECK(physical_position[X_AXIS] == contacted - 20);
    CHECK(hal.probe.get_state().probe_id == Probe_2 && explicit_selection_calls == 2);
    CHECK(explicit_probe_block("G21G90G0X0") == Status_OK);
    CHECK(protocol_buffer_synchronize());
    CHECK(physical_position[X_AXIS] == 0 && sys.position[X_AXIS] == 0);
    CHECK(plan_get_current_block() == NULL && state_get() == STATE_IDLE);
    CHECK(sys.alarm == Alarm_None && !sys.abort);
    return EXIT_SUCCESS;
}
