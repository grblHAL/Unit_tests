#include "support/encoder_thread_motion_host.h"
#include "check.h"
static bool requested_hold;
static unsigned held_polls, held_pulses;
static int32_t held_z;
static coolant_state_t no_coolant(void) { return (coolant_state_t){0}; }
static void hold_feed_per_revolution(sys_state_t state)
{
    service_sync_parser_driver(state);
    if(!requested_hold && state == STATE_CYCLE && axis_pulses[Z_AXIS] >= 20) {
        CHECK(!sys.override.control.sync && !sys.override.control.feed_hold_disable);
        requested_hold = true;
        CHECK(protocol_enqueue_realtime_command(CMD_FEED_HOLD));
    }
    CHECK(!sys.flags.feed_hold_pending);
    if(state_get() == STATE_HOLD && sys.holding_state == Hold_Complete) {
        if(held_polls == 0) {
            held_z = physical_position[Z_AXIS];
            held_pulses = axis_pulses[Z_AXIS];
            CHECK(held_z > 0 && held_z < 800);
        }
        CHECK(physical_position[Z_AXIS] == held_z && axis_pulses[Z_AXIS] == held_pulses);
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
    grbl.on_execute_realtime = hold_feed_per_revolution;
    CHECK(sync_parser_block("G95G1Z10F1") == Status_OK);
    CHECK(protocol_buffer_synchronize());
    CHECK(requested_hold && held_polls == 4);
    CHECK(physical_position[Z_AXIS] == 800 && axis_pulses[Z_AXIS] == 800);
    CHECK(axis_pulses[X_AXIS] == 0 && axis_pulses[Y_AXIS] == 0);
    CHECK(plan_get_current_block() == NULL && state_get() == STATE_IDLE);
    CHECK(!sys.abort && sys.alarm == Alarm_None && thread_encoder_state.on);
    return EXIT_SUCCESS;
}
