#include "support/status_refresh_host.h"

int main(void)
{
    prepare_refresh_cycle();
    next_refresh_report();
    next_refresh_report();
    settings.status_report.sync_on_wco_change = false;
    char offset[] = "G10L2P2X5", select[] = "G55";
    CHECK(gc_execute_block(offset) == Status_OK);
    CHECK(gc_execute_block(select) == Status_OK);
    CHECK(protocol_enqueue_realtime_command(CMD_OVERRIDE_FEED_COARSE_PLUS));
    CHECK(protocol_exec_rt_system());
    CHECK(sys.override.feed_rate == 110);
    next_refresh_report();
    CHECK(strstr(engine_output, "|Ov:110,100,100") != NULL);
    CHECK(strstr(engine_output, "|WCO:5.000,0.000,0.000") != NULL);
    CHECK(strstr(engine_output, "|WCS:G55") != NULL);
    CHECK(state_get() == STATE_CYCLE && plan_get_current_block() != NULL);
    finish_motion_pulses();
    CHECK(protocol_exec_rt_system());
    CHECK(state_get() == STATE_IDLE && plan_get_current_block() == NULL);
    CHECK(physical_position[X_AXIS] == 1600 && axis_pulses[X_AXIS] == 1600);
    CHECK(gc_state.modal.g5x_offset.id == CoordinateSystem_G55);
    return EXIT_SUCCESS;
}
