#pragma once
#include "support/segmented_stop_stream_host.h"

static unsigned sender_dwell_intervals;
static bool stop_only_from_dwell(void) { return false; }
static void sender_stop_at_dwell(uint32_t milliseconds, delay_callback_ptr callback)
{
    engine_ticks += milliseconds;
    if(!program_stop_sent && milliseconds == DWELL_TIME_STEP && physical_position[Z_AXIS] == -160) {
        sender_dwell_intervals++;
        program_stop_sent = true;
        CHECK(protocol_enqueue_realtime_command(CMD_STOP));
    }
    if(callback) callback();
}
static inline void run_dwell_sender_stop(const char *program)
{
    prepare_jog_motion();
    configure_stopped_program_stream(program);
    program_should_stop = stop_only_from_dwell;
    hal.delay_ms = sender_stop_at_dwell;
    finish_stopped_program();
    CHECK(sender_dwell_intervals == 1);
    CHECK(program_stop_position[Z_AXIS] == -160);
    CHECK(physical_position[Z_AXIS] == -160 && axis_pulses[Z_AXIS] == 160);
    CHECK(program_line_reads <= 3); // Cancel discards the unread tail; recovery adds one line.
}
