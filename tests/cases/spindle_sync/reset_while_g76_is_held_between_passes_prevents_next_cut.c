#include "support/thread_reset_motion_host.h"
static bool hold_requested;
static unsigned held_polls, held_pulses[N_AXIS];
static int32_t held_position[N_AXIS];
static coolant_state_t no_coolant(void) { return (coolant_state_t){0}; }
static bool reset_after_completed_thread_hold(sys_state_t state)
{
    if(!hold_requested && state == STATE_CYCLE && axis_pulses[Z_AXIS] >= 20) {
        CHECK(sys.override.control.sync && sys.override.control.feed_hold_disable);
        hold_requested = true;
        CHECK(protocol_enqueue_realtime_command(CMD_FEED_HOLD));
    }
    if(state_get() != STATE_HOLD || sys.holding_state != Hold_Complete)
        return false;
    CHECK(hold_requested && sync_encoder_resets == 1);
    CHECK(physical_position[Z_AXIS] == -80 && thread_encoder_state.on);
    if(held_polls == 0) {
        memcpy(held_position, physical_position, sizeof(held_position));
        memcpy(held_pulses, axis_pulses, sizeof(held_pulses));
    }
    for(unsigned axis = 0; axis < N_AXIS; axis++) {
        CHECK(physical_position[axis] == held_position[axis]);
        CHECK(axis_pulses[axis] == held_pulses[axis]);
    }
    return ++held_polls == 4;
}
int main(void)
{
    prepare_thread_reset();
    hal.coolant.get_state = no_coolant;
    thread_reset_condition = reset_after_completed_thread_hold;
    (void)sync_parser_block("G76Z-1P1I-1J0.5K1");
    CHECK(hold_requested && held_polls == 4);
    check_thread_reset_stops_pulses();
    CHECK(sync_encoder_resets == 1 && !sys.position_lost);
    for(unsigned axis = 0; axis < N_AXIS; axis++)
        CHECK(physical_position[axis] == held_position[axis]);
    return EXIT_SUCCESS;
}
