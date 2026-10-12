#pragma once
#include "support/report_host.h"
#include "stream.h"
#include "protocol.h"
static char primary_output[1024], secondary_output[1024];
static bool primary_up = true, secondary_up = true;
static unsigned connection_changes;
static enqueue_realtime_command_ptr primary_rt, secondary_rt;
static bool primary_connected(void) { return primary_up; }
static bool secondary_connected(void) { return secondary_up; }
static void primary_write(const char *text) { CHECK(strlen(primary_output) + strlen(text) < sizeof(primary_output)); strcat(primary_output, text); }
static void secondary_write(const char *text) { CHECK(strlen(secondary_output) + strlen(text) < sizeof(secondary_output)); strcat(secondary_output, text); }
static enqueue_realtime_command_ptr primary_handler(enqueue_realtime_command_ptr handler) { enqueue_realtime_command_ptr previous = primary_rt; primary_rt = handler; return previous; }
static enqueue_realtime_command_ptr secondary_handler(enqueue_realtime_command_ptr handler) { enqueue_realtime_command_ptr previous = secondary_rt; secondary_rt = handler; return previous; }
static void stream_changed(void) { connection_changes++; }
static const io_stream_t primary_connection = {.type = StreamType_Serial, .instance = 0, .write = primary_write, .is_connected = primary_connected, .set_enqueue_rt_handler = primary_handler};
static const io_stream_t secondary_connection = {.type = StreamType_Telnet, .instance = 0, .write = secondary_write, .is_connected = secondary_connected, .set_enqueue_rt_handler = secondary_handler};
static inline void prepare_stream_connections(void)
{
    prepare_report();
    grbl.on_stream_changed = stream_changed;
    CHECK(stream_connect(&primary_connection));
    CHECK(primary_rt == protocol_enqueue_realtime_command);
}
static inline void clear_connection_output(void) { primary_output[0] = secondary_output[0] = '\0'; }
