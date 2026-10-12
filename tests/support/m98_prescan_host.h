#pragma once
#include "support/flow_file_host.h"
#include "support/macro_parser_host.h"
static inline void prepare_m98_prescan(void)
{
    prepare_flow_file();
    grbl.on_macro_execute = capture_macro;
    hal.stream.state.m98_macro_prescan = true;
}
