#include "support/status_refresh_host.h"

int main(void)
{
    prepare_refresh_cycle();
    next_refresh_report();
    next_refresh_report();
    settings.status_report.sync_on_wco_change = false;
    offset_id_t first_offset = st_get_offset_id();
    char zero[] = "G92X0", next_cut[] = "G1X5";
    CHECK(gc_execute_block(zero) == Status_OK);
    CHECK(gc_execute_block(next_cut) == Status_OK);
    next_refresh_report();
    CHECK(strstr(engine_output, "|WCO:0.000,0.000,0.000") != NULL);
    CHECK(state_get() == STATE_CYCLE && plan_get_current_block() != NULL);

    for(unsigned ticks = 0; ticks < 200000 && st_get_offset_id() == first_offset; ticks++) {
        st_prep_buffer();
        stepper_driver_interrupt_handler();
    }
    CHECK(st_get_offset_id() != first_offset);
    CHECK(physical_position[X_AXIS] >= 1600 && physical_position[X_AXIS] < 2000);
    CHECK(protocol_enqueue_realtime_command(CMD_OVERRIDE_FEED_COARSE_PLUS));
    CHECK(protocol_exec_rt_system());
    CHECK(sys.override.feed_rate == 110);
    next_refresh_report();
    CHECK(strstr(engine_output, "|Ov:110,100,100") != NULL);
    CHECK(strstr(engine_output, "|WCO:20.000,0.000,0.000") != NULL);
    next_refresh_report();
    CHECK(strstr(engine_output, "|WCO:") == NULL);
    CHECK(state_get() == STATE_CYCLE && plan_get_current_block() != NULL);

    finish_motion_pulses();
    CHECK(protocol_exec_rt_system());
    CHECK(state_get() == STATE_IDLE && plan_get_current_block() == NULL);
    CHECK(physical_position[X_AXIS] == 2000 && axis_pulses[X_AXIS] == 2000);
    CHECK(sys.position[X_AXIS] == 2000);
    NEAR(gc_state.position[X_AXIS], 25);
    NEAR(gc_state.g92_offset.coord.values[X_AXIS], 20);
    return EXIT_SUCCESS;
}
