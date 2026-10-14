#pragma once
#include "support/stream_connection_host.h"
static char third_output[1024];
static void third_write(const char *text)
{ CHECK(strlen(third_output) + strlen(text) < sizeof(third_output)); strcat(third_output,text); }
static io_stream_t third_connection;
static inline void prepare_three_streams(void)
{
    prepare_stream_connections(); CHECK(stream_connect(&secondary_connection));
    third_connection = secondary_connection; third_connection.instance = 1;
    third_connection.write = third_write; CHECK(stream_connect(&third_connection));
}
static inline void clear_three_outputs(void)
{ clear_connection_output(); third_output[0] = 0; }
