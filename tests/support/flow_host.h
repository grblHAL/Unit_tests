#pragma once
#include "support/engine_host.h"
#include "ngc_flowctrl.h"
#include "check.h"
#include <string.h>

static bool flow_skip;

static inline void prepare_flow(void)
{
    engine_parser_prepare();
    ngc_flowctrl_init();
    flow_skip = false;
}

static inline status_code_t flow_command(uint32_t label, const char *command)
{
    char line[128];
    uint_fast8_t pos = 0;
    CHECK(strlen(command) < sizeof(line));
    strcpy(line, command);
    status_code_t status = ngc_flowctrl(label, 1, line, &pos, &flow_skip);
    CHECK(pos <= strlen(command));
    return status;
}
