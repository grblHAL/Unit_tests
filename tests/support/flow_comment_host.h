#pragma once
#include "support/report_host.h"
#include "ngc_flowctrl.h"
#include "ngc_params.h"
#include <stdlib.h>
static unsigned prior_comment_calls, process_comment_calls;
static status_code_t prior_comment_status = Status_OK;
static const char *processed_message;
static status_code_t prior_comment(char *comment)
{
    CHECK(comment != NULL);
    prior_comment_calls++;
    return prior_comment_status;
}
static char *process_comment(char *comment)
{
    CHECK(comment != NULL && comment[0] == '!');
    process_comment_calls++;
    if(processed_message == NULL)
        return NULL;
    char *message = malloc(strlen(processed_message) + 1);
    CHECK(message != NULL);
    return strcpy(message, processed_message);
}
static inline void prepare_flow_comment(void)
{
    engine_prepare();
    hal.stream.is_connected = connected;
    report_init_fns();
    report_init();
    grbl.on_gcode_comment = prior_comment;
    grbl.on_process_gcode_comment = process_comment;
    ngc_flowctrl_init();
    engine_output[0] = '\0';
}
