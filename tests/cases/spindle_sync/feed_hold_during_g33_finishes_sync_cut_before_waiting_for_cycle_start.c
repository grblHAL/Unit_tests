#include "support/encoder_thread_motion_host.h"
#include "check.h"
static bool requested_hold, observed_pending;
static unsigned held_polls;
static coolant_state_t no_coolant(void) { return (coolant_state_t){0}; }
static void request_hold_during_sync(sys_state_t state)
{
    service_sync_parser_driver(state);
    if(!requested_hold && state == STATE_CYCLE && axis_pulses[Z_AXIS] >= 20) {
        CHECK(sys.override.control.sync && sys.override.control.feed_hold_disable);
        CHECK(axis_pulses[Z_AXIS] < 800);
        requested_hold = true;
        CHECK(protocol_enqueue_realtime_command(CMD_FEED_HOLD));
    }
    if(sys.flags.feed_hold_pending && state_get() == STATE_CYCLE) {
        observed_pending = true;
        CHECK(state_get_substate() == 1);
    }
    if(state_get() == STATE_HOLD && sys.holding_state == Hold_Complete) {
        CHECK(physical_position[Z_AXIS] == 800 && axis_pulses[Z_AXIS] == 800);
        CHECK(thread_encoder_state.on);
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
    grbl.on_execute_realtime = request_hold_during_sync;
    CHECK(sync_parser_block("G33Z10K1") == Status_OK);
    CHECK(protocol_execute_realtime());
    CHECK(requested_hold && observed_pending && held_polls == 4);
    CHECK(!sys.flags.feed_hold_pending && !sys.abort && sys.alarm == Alarm_None);
    CHECK(sys.override.control.value == original.value);
    CHECK(physical_position[Z_AXIS] == 800 && axis_pulses[Z_AXIS] == 800);
    CHECK(sync_parser_block("G1Z11F100") == Status_OK);
    CHECK(protocol_buffer_synchronize());
    CHECK(physical_position[Z_AXIS] == 880 && axis_pulses[Z_AXIS] == 880);
    CHECK(axis_pulses[X_AXIS] == 0 && axis_pulses[Y_AXIS] == 0);
    CHECK(plan_get_current_block() == NULL && state_get() == STATE_IDLE);
    return EXIT_SUCCESS;
}
