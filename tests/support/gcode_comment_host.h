#pragma once
#include "support/report_host.h"
#include "state_machine.h"
static unsigned plain_comment_calls, process_comment_calls, message_output_calls;
static char captured_comment[128], captured_message[128];
static const char *plugin_message;
static status_code_t plain_comment_status = Status_OK;
static bool consume_output_message;
static status_code_t capture_plain_comment(char *text)
{
    CHECK(strlen(text) < sizeof(captured_comment));
    strcpy(captured_comment, text); plain_comment_calls++;
    return plain_comment_status;
}
static char *process_plugin_comment(char *text)
{
    CHECK(text != NULL); process_comment_calls++;
    if(!plugin_message) return NULL;
    char *message = malloc(strlen(plugin_message) + 1);
    CHECK(message != NULL);
    return strcpy(message, plugin_message);
}
static status_code_t capture_output_message(char *text)
{
    CHECK(strlen(text) < sizeof(captured_message));
    strcpy(captured_message, text); message_output_calls++;
    if(consume_output_message) *text = '\0';
    return Status_OK;
}
static inline void prepare_gcode_comments(void)
{
    prepare_report(); state_set(STATE_IDLE); engine_output[0] = '\0';
    grbl.on_process_gcode_comment = process_plugin_comment;
    grbl.on_gcode_comment = capture_plain_comment;
    grbl.on_gcode_message = capture_output_message;
}
