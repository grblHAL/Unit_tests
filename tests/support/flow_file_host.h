#pragma once
#include "support/flow_host.h"
#include "support/file_stream_host.h"
#include "ngc_params.h"

static inline void prepare_flow_file(void)
{
    prepare_file_stream("0123456789");
    ngc_flowctrl_init();
    flow_skip = false;
    CHECK(stream_redirect_read("/fixture/program", NULL, NULL) != NULL);
}

static inline void close_flow_file(void)
{
    ngc_flowctrl_init();
    stream_redirect_close(hal.stream.file);
    CHECK(file_closes == 1);
}
