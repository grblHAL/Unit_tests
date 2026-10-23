#include "support/encoder_thread_motion_host.h"
static bool hold_requested, first_cut_finished;
static unsigned held_polls, held_pulses[N_AXIS];
static int32_t held_position[N_AXIS];
static coolant_state_t no_coolant(void) { return (coolant_state_t){0}; }
static void hold_multipass_thread(sys_state_t state)
{
    service_sync_parser_driver(state);
    if(!hold_requested && state == STATE_CYCLE && axis_pulses[Z_AXIS] >= 20) {
        CHECK(sys.override.control.sync && sys.override.control.feed_hold_disable);
        hold_requested = true;
        CHECK(protocol_enqueue_realtime_command(CMD_FEED_HOLD));
    }
    if(hold_requested && physical_position[Z_AXIS] == -80)
        first_cut_finished = true;
    if(state_get() == STATE_HOLD && sys.holding_state == Hold_Complete) {
        CHECK(first_cut_finished && sync_encoder_resets == 1);
        CHECK(thread_encoder_state.on);
        if(held_polls == 0) {
            memcpy(held_position, physical_position, sizeof(held_position));
            memcpy(held_pulses, axis_pulses, sizeof(held_pulses));
        }
        for(unsigned axis = 0; axis < N_AXIS; axis++) {
            CHECK(physical_position[axis] == held_position[axis]);
            CHECK(axis_pulses[axis] == held_pulses[axis]);
        }
        if(++held_polls == 4)
            CHECK(protocol_enqueue_realtime_command(CMD_CYCLE_START));
        CHECK(held_polls <= 4);
    }
}
int main(void)
{
    prepare_encoder_thread_motion();
    hal.coolant.get_state = no_coolant;
    gc_override_flags_t original = sys.override.control;
    grbl.on_execute_realtime = hold_multipass_thread;
    CHECK(sync_parser_block("G76Z-1P1I-1J0.5K1") == Status_OK);
    CHECK(protocol_buffer_synchronize());
    CHECK(hold_requested && first_cut_finished && held_polls == 4);
    CHECK(sync_encoder_resets == 2);
    CHECK(physical_position[X_AXIS] == 800 && physical_position[Z_AXIS] == -80);
    CHECK(axis_pulses[X_AXIS] == 560 && axis_pulses[Z_AXIS] == 240);
    CHECK(axis_pulses[Y_AXIS] == 0);
    CHECK(sys.override.control.value == original.value);
    CHECK(!sys.flags.feed_hold_pending && !sys.abort && sys.alarm == Alarm_None);
    CHECK(plan_get_current_block() == NULL && state_get() == STATE_IDLE);
    return EXIT_SUCCESS;
}
