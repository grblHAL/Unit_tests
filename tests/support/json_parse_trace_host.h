#pragma once
#include "support/engine_host.h"
#include "vfs.h"
#include "stream_json.h"
#include "check.h"
#include <string.h>
static unsigned json_trace_calls;
static char json_trace_tags[8][32], json_trace_values[8][64];
static bool json_trace_strings[8];
static const char *json_stop_tag;
static bool json_trace_callback(char *tag, char *value, bool is_string, void *data)
{
    CHECK(data == &json_trace_calls && json_trace_calls < 8);
    CHECK(strlen(tag) < sizeof(json_trace_tags[0]) && strlen(value) < sizeof(json_trace_values[0]));
    strcpy(json_trace_tags[json_trace_calls], tag);
    strcpy(json_trace_values[json_trace_calls], value);
    json_trace_strings[json_trace_calls++] = is_string;
    return json_stop_tag && strcmp(tag, json_stop_tag) == 0;
}
static inline bool parse_json_trace(char *text)
{
    return json_parse_string(text, json_trace_callback, &json_trace_calls);
}
